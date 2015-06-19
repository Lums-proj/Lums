require 'json'

class JsonCompiler
  def initialize folder
    @objects = []
    Dir[folder + '/*.json'].each do |file|
      @objects << read_json(file)
    end
  end

  def run! file
    buffer = ''
    buffer << [@objects.size].pack('L<')
    @objects.each do |object|
      write_object buffer, object
    end
    File.write file, buffer
  end

  private

  def read_json file
    JSON.parse(File.read file)
  end

  def write_object buffer, object
    buffer << 'o'
    buffer << [object.size].pack('L<')
    object.each do |key, value|
      buffer << [key.size, key].pack('L<A*')
      write_value buffer, value
    end
  end

  def write_array buffer, array
    buffer << 'a'
    buffer << [array.size].pack('L<')
    array.each do |value|
      write_value buffer, value
    end
  end

  def write_value buffer, value
    case value
    when String
      buffer << ['s'.ord, value.size, value].pack('cL<A*')
    when Integer
      buffer << ['i'.ord, value.to_i].pack('cL<')
    when Float
      buffer << ['f'.ord, value.to_f].pack('cF')
    when Hash
      write_object buffer, value
    when Array
      write_array buffer, value
    end
  end

end

if ARGV.size != 2
  puts "usage: json2lums <folder> <objects.bin>"
else
  jc = JsonCompiler.new ARGV[0]
  jc.run! ARGV[1]
end