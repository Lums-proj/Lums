require 'json'
require 'ap'

class Spiner
  def initialize spine, atlas
    @atlas = read_atlas atlas
    root = JSON.parse(File.read spine)
    read_bones root
    read_skins root
    read_iks root
    read_animations root
  end

  def run! spine, atlas
    buffer = ''
    write_bones buffer
    write_skins buffer
    write_iks buffer
    write_animations buffer
    f = File.open spine, 'wb'
    f.write buffer
    f.close

    buffer = ''
    write_atlas buffer
    f = File.open atlas, 'wb'
    f.write buffer
    f.close
  end

  private

  def read_atlas file
    buffer = File.read file
    array = buffer.split "\n"
    header = array.shift 6
    size = header[2].split(' ')[1].split(',').map(&:to_i)
    atlas = []
    array.each_slice 7 do |b|
      hash = {}
      hash[:name] = b[0]
      hash[:pos] = []
      hash[:pos][0] = b[2].split(' ')[1].to_f / size[0].to_f
      hash[:pos][1] = b[2].split(' ')[2].to_f / size[1].to_f
      hash[:size] = []
      hash[:size][0] = b[3].split(' ')[1].to_f / size[0].to_f
      hash[:size][1] = b[3].split(' ')[2].to_f / size[1].to_f      
      atlas << hash
    end
    {size: size, atlas: atlas}
  end

  def write_atlas buffer
    buffer << [@atlas[:atlas].size].pack('L<')
    @atlas[:atlas].each do |h|
      buffer << h[:pos].pack('FF')
      buffer << h[:size].pack('FF')
    end
  end

  def read_bones root
    @bones = []
    root['bones'].each do |b|
      bone = []
      bone << b['name'].size
      bone << b['name']
      bone << ((@bones.find_index {|o| o[1] == b['parent']}) || -1)
      bone << (b['length'] || 0).to_f
      bone << (b['x'] || 0).to_f
      bone << (b['y'] || 0).to_f
      bone << (b['scaleX'] || 1).to_f
      bone << (b['scaleY'] || 1).to_f
      bone << (b['rotation'] || 0).to_f
      ir = b['inheritRotation']
      ir = true if ir.nil?
      bone << (ir ? 1 : 0)
      @bones << bone
    end
  end

  def write_bones buffer
    buffer << [@bones.size].pack('L<')
    @bones.each {|b| buffer << b.pack('L<A*l<FFFFFFC')}
  end

  def read_skins root
    @skins = []
    skin = {}
    root['skins'].each_value {|s| skin.merge! s}
    root['slots'].each do |s|
      next if s['attachment'].nil?
      key = s['name']
      value = skin[key]
      bone = s['bone']
      bone_id = @bones.find_index {|b| b[1] == bone}
      value.each do |key, value|
        break unless value["type"].nil?
        name = value['name'] || key
        texture = @atlas[:atlas].find_index{|h| h[:name] == name}
        x = value['x'].to_f
        y = value['y'].to_f
        rotation = value['rotation'].to_f
        @skins << [texture, bone_id, x, y, rotation]
      end
    end
  end

  def write_skins buffer
    buffer << [@skins.size].pack('L<')
    @skins.each {|s| buffer << s.pack('l<L<FFF')}
  end

  def read_iks root
    iks = root['ik']
    @iks = []
    iks.each do |ik|
      ik_data = {}
      ik_data[:target] = @bones.find_index {|b| b[1] == ik['target']}
      ik_data[:bones] = ik['bones'].map {|b| @bones.find_index {|bb| bb[1] == b }}
      ik_data[:bones] << -1 if ik_data[:bones].size == 1
      ik_data[:bend_positive] = ik['bendPositive'].nil? ? 1 : (ik['bendPositive'] ? 1 : 0)
      @iks << ik_data
    end
  end

  def write_iks buffer
    buffer << [@iks.size].pack('L<')
    @iks.each do |ik|
      buffer << ([ik[:target]] + ik[:bones] + [ik[:bend_positive]]).pack('L<L<L<C')
    end
  end

  def read_animations root
    @animations = []
    root['animations'].each do |key, value|
      anim = {}
      anim[:name] = key
      bones = []
      value['bones'].each do |k, v|
        bone = {}
        bone[:bone] = @bones.find_index {|b| b[1] == k}
        bone[:rotate] = []
        bone[:translate] = []
        # 0 for rotation
        # 1 for translation
        # 2 for scale
        if v['rotate']
          v['rotate'].each do |vv|
            rot = {}
            time = (vv['time'] * 120.0).round.to_i
            angle = (vv['angle'] || 0)
            # 0 linear
            # 1 stepped
            # 2 bezier
            curve = 0
            curve = 1 if vv['curve'] == "stepped"
            curve = 2 if vv['curve'].class == Array
            rot[:time] = time
            rot[:angle] = angle
            rot[:curve] = curve
            rot[:bezier] = vv['curve'] if curve == 2
            bone[:rotate] << rot
          end
        end
        if v['translate']
          v['translate'].each do |vv|
            t = {}
            time = (vv['time'] * 120.0).round.to_i
            x = (vv['x'] || 0.0).to_f
            y = (vv['y'] || 0.0).to_f
            curve = 0
            curve = 1 if vv['curve'] == "stepped"
            curve = 2 if vv['curve'].class == Array
            t[:time] = time
            t[:x] = x
            t[:y] = y
            t[:curve] = curve
            t[:bezier] = vv['curve'] if curve == 2
            bone[:translate] << t
          end
        end
        bones << bone
      end
      anim[:bones] = bones
      @animations << anim
    end
  end

  def write_animations buffer
    buffer << [@animations.size].pack('L<')
    @animations.each do |anim|
      name = anim[:name]
      buffer << [name.size, name].pack('L<A*')
      buffer << [anim[:bones].size].pack('L<')
      anim[:bones].each do |bone|
        id = bone[:bone]
        rotate = bone[:rotate]
        translate = bone[:translate]
        buffer << [id, rotate.size, translate.size].pack('L<L<L<')
        rotate.each do |rot|
          buffer << [rot[:time], rot[:angle], rot[:curve]].pack('L<FC')
          if rot[:curve] == 2
            buffer << rot[:bezier].pack('L<L<L<L<')
          end
        end
        translate.each do |t|
          buffer << [t[:time], t[:x], t[:y], t[:curve]].pack('L<FFC')
          if t[:curve] == 2
            buffer << t[:bezier].pack('L<L<L<L<')
          end
        end
      end
    end
  end
end

if ARGV.size != 4
  puts "usage: spine2lums <spine.json> <spine.atlas> <anim.bin> <atlas.bin>"
else
  spiner = Spiner.new ARGV[0], ARGV[1]
  spiner.run! ARGV[2], ARGV[3] 
end
