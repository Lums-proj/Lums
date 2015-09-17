class Slot

  attr_reader :name, :bone

  def read spine, object
    @name = object['name']
    @bone = spine.find_bone_index object['bone']
    @attachment = object['attachment']
  end

  def serialize spine
    [@bone, spine.find_attachment_index(@attachment)].pack('L<l<')
  end

end
