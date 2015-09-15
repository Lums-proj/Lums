module KeyFrame
  class KeyFrame

    attr_accessor :time

    def initialize
      @time = nil
    end

    def serialize
      [@time].pack('L<')
    end

    def read object
      @time = (object['time'] * 60).round.to_i
    end

  end

end