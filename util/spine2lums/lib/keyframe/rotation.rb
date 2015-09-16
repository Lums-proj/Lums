require_relative 'keyframe'

module KeyFrame
  class Rotation < KeyFrame
    
    attr_accessor :angle, :curve

    def initialize
      @curve = Curve.new 
    end  

    def serialize
      super + [@angle].pack('F') + @curve.serialize
    end

    def read _, object
      super
      @angle = object['angle'] || 0.0
      @curve.read object
    end

  end

end