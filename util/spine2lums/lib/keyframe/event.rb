require_relative 'keyframe'

module KeyFrame
  class Event < KeyFrame
    
    attr_accessor :name

    def initialize
      @name = '' 
    end  

    def serialize
      super + [@name.size, @name].pack('L<a*')
    end

    def read _, object
      super
      @name = object['name']
    end

  end

end