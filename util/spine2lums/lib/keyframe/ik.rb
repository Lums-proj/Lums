require_relative 'keyframe'

module KeyFrame
  class Ik < KeyFrame

    def serialize
      super + [@bend ? 1 : 0].pack('C')
    end

    def read _, object
      super
      @bend = object['bendPositive'].nil? ? true : object['bendPositive']
    end

  end

end