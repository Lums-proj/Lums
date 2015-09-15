require_relative 'keyframe'

module KeyFrame
  class Event < KeyFrame
    
    attr_accessor :name

    def initialize
      @name = '' 
    end  

    def serialize
      super + [@name.count, @name].pack('L<a*')
    end

    def read object
      super
      @name = object['name']
    end

  end

end