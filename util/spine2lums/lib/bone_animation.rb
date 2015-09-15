require_relative 'keyframe/translation'
require_relative 'keyframe/rotation'


class BoneAnimation

  def initialize
    @translations = []
    @rotations = []
  end

  def serialize
    i = spine.bones.find_index{|b| b.name == @name}
    buffer = [i].pack('L<')
    buffer << pack_array(@translations)
    buffer << pack_array(@rotations)
    buffer
  end

  def read key, value
    @name = key
    read_array(value, KeyFrame::Translation, @translations, 'translate')
    read_array(value, KeyFrame::Rotation, @rotations, 'rotate')
  end

  private

  def pack_array array
    [array.count].pack('L<') + array.map(&:serialize).reduce(:+)
  end

  def read_array object, klass, array, key
    return if object[key].nil?
    object[key].each do |o|
      k = klass.new
      k.read o
      array << k
    end
  end

end