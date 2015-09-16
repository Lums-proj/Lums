require_relative 'keyframe'

module KeyFrame
  class Attachment < KeyFrame

    def serialize
      super + [@attachment].pack('l<')
    end

    def read spine, object
      super
      @attachment = spine.find_attachment_index object['name']
    end
  end
end