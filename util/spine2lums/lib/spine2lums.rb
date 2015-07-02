require 'json'

class Spiner
  def initialize spine, atlas
    @atlas = read_atlas atlas
    root = JSON.parse(File.read spine)
    read_bones root
    read_skins root
  end

  def run! spine, atlas
    buffer = ''
    write_bones buffer
    write_skins buffer
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
      bone << (b['x'] || 0).to_f
      bone << (b['y'] || 0).to_f
      bone << (b['scaleX'] || 1).to_f
      bone << (b['scaleY'] || 1).to_f
      bone << (b['rotation'] || 0).to_f
      @bones << bone
    end
  end

  def write_bones buffer
    buffer << [@bones.size].pack('L<')
    @bones.each {|b| buffer << b.pack('L<A*l<FFFFF')}
  end

  def read_skins root
    @skins = []
    skin = {}
    root['skins'].each_value {|s| skin.merge! s}
    skin.each do |key, value|
      bone = root['slots'].find{|h| h['name'] == key }['bone']
      bone_id = @bones.find_index {|b| b[1] == bone}
      value.each do |key, value|
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

end

if ARGV.size != 4
  puts "usage: spine2lums <spine.json> <spine.atlas> <anim.bin> <atlas.bin>"
else
  spiner = Spiner.new ARGV[0], ARGV[1]
  spiner.run! ARGV[2], ARGV[3] 
end
