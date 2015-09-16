class Curve

  CURVE_TYPES = {
    linear: 0,
    stepped: 1,
    bezier: 2
  }

  def initialize
  end

  def read object
    curve = object['curve']
    @type = :linear if curve.nil? || curve == 'linear'
    @type = :stepped if curve == 'stepped'
    if curve.class == Array
      @type = :bezier
      @values = curve
    end
  end

  def serialize
    buffer = [CURVE_TYPES[@type]].pack('C')
    if @type == :bezier
      buffer << @values.pack('FFFF')
    end
    buffer
  end

end