require 'json'

class Spliner
  def initialize file
    root = JSON.parse(File.read file)
    read_bones root
  end

  def run! file
    puts "Bones"
    p @bones
    buffer = ""
    write_bones buffer
    f = File.open file, 'wb'
    f.write buffer
    f.close
  end

  private

  def read_bones root
    @bones = []
    root['bones'].each do |b|
      bone = []
      bone << b['name']
      bone << ((@bones.find_index {|o| o[0] == b['parent']}) || 0)
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
    @bones.each {|b| buffer << b.pack('Z*L<FFFFF')}
  end
end

if ARGV.size != 2
  puts "usage: spline2lums <spline.json> <output>"
else
  spliner = Spliner.new ARGV[0]
  spliner.run! ARGV[1]
end
