class Attachment

  attr_reader :name

  def read spine, bone, key, value
    @name = key
    @bone = spine.slots[spine.find_slot_index(bone)].bone
    @x = value['x'] || 0.0
    @y = value['y'] || 0.0
    @scale_x = value['scaleX'] || 1.0
    @scale_y = value['scaleY'] || 1.0
    @rotation = value['rotation'] || 0.0
    @texture = spine.find_texture_index key
  end

  def serialize spine
    [@x, @y, @scale_x, @scale_y, @rotation, @bone, @texture].pack('FFFFFl<l<')
  end

end
