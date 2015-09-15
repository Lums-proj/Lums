class Bone

  attr_reader :name

  def serialize
    [@name.count, @name, @parent, @x, @y, @length, @scale_x, @scale_y, @rotation, @inherit_rotation ? 1 : 0].pack('L<a*l<FFFFFFC')
  end

  def read spine, object
    @name = object['name']
    @parent = spine.find_bone_index object['parent']
    @x = object['x'] || 0.0
    @y = object['y'] || 0.0
    @length = object['length'] || 0.0
    @scale_x = object['scaleX'] || 1.0
    @scale_y = object['scaleY'] || 1.0
    @rotation = object['rotation'] || 0.0
    @inherit_rotation = object['inheritRotation'].nil? ? true : object['inheritRotation']
  end

end