class Bone

  attr_reader :name

  def serialize
    [@name.size, @name, @x, @y, @scale_x, @scale_y, @rotation, @length, @parent, @inherit_rotation ? 1 : 0].pack('L<a*FFFFFFl<C')
  end

  def read spine, object
    @name = object['name']
    @x = object['x'] || 0.0
    @y = object['y'] || 0.0
    @scale_x = object['scaleX'] || 1.0
    @scale_y = object['scaleY'] || 1.0
    @rotation = object['rotation'] || 0.0
    @length = object['length'] || 0.0
    @parent = spine.find_bone_index object['parent']
    @inherit_rotation = object['inheritRotation'].nil? ? true : object['inheritRotation']
  end

end