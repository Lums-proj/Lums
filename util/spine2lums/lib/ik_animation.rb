require_relative 'keyframe/ik'

class IkAnimation

  def initialize
    @iks = []
  end

  def serialize spine
    i = spine.iks.find_index{|ik| ik.name == @name}
    buffer = [i, @iks.count].pack('L<L<')
    @iks.each do |ik|
      buffer << ik.serialize
    end
    buffer
  end

  def read key, values
    @name = key
    values.each do |o|
      ik = KeyFrame::Ik.new
      ik.read o
      @iks << ik
    end
  end

end