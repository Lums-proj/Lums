require_relative 'keyframe/ik'

class IkAnimation

  def initialize
    @iks = []
  end

  def serialize
    buffer = [@ik, @iks.count].pack('l<L<')
    @iks.each do |ik|
      buffer << ik.serialize
    end
    buffer
  end

  def read spine, key, values
    @name = key
    @ik = spine.find_ik_index @name
    values.each do |o|
      ik = KeyFrame::Ik.new
      ik.read spine, o
      @iks << ik
    end
  end

end