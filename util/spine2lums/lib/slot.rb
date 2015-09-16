class Slot

  attr_reader :name

  def read spine, object
    @name = object['name']
    @bone = spine.find_bone_index object['bone']
    @attachment = spine.find_attachment_index object['attachment']
  end

  def serialize
    [@bone, @attachment].pack('L<l<')
  end

end
