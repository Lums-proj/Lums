require_relative 'keyframe/attachment'

class SlotAnimation

  def initialize
    @attachments = []
  end

  def read spine, key, value
    @slot = spine.find_slot_index key
    value['attachment'].each do |object|
      attachment = KeyFrame::Attachment.new
      attachment.read spine, object
      @attachments << attachment
    end
  end

  def serialize
    buffer = [@slot, @attachments.count].pack('l<L<')
    buffer << @attachments.map(&:serialize).reduce(:+) unless @attachments.empty?
    buffer
  end
end