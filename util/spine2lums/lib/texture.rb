class Texture

  attr_reader :name

  def read block, size
    @name = block[0]
    @x = block[2].split(' ')[1].to_f / size[0].to_f
    @y = block[2].split(' ')[2].to_f / size[1].to_f
    @w = block[3].split(' ')[1].to_f / size[0].to_f
    @h = block[3].split(' ')[2].to_f / size[1].to_f 
  end

  def serialize
    [@x, @y, @w, @h].pack('FFFF')
  end

end