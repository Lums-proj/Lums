class Attachment

  attr_reader :name

  def read spine, key, value
    @name = key
    @x = value['x'] || 0.0
    @y = value['y'] || 0.0
    @scale_x = value['scaleX'] || 1.0
    @scale_y = value['scaleY'] || 1.0
    @rotation = value['rotation'] || 0.0
    @texture = spine.find_texture_index key
  end

  def serialize
    [@x, @y, @scale_x, @scale_y, @rotation, @texture].pack('FFFFFl<')
  end

end
