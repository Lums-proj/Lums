require_relative 'keyframe'
require_relative '../curve'

module KeyFrame
  class Translation < KeyFrame
    
    attr_accessor :angle, :curve

    def initialize
      @curve = Curve.new 
    end  

    def serialize
      super + [@x, @y].pack('FF') + @curve.serialize
    end

    def read object
      super
      @x = object['x'] || 0.0
      @y = object['y'] || 0.0
      @curve.read object
    end

  end

end