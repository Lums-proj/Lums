require_relative 'keyframe/translation'
require_relative 'keyframe/rotation'


class BoneAnimation

  def initialize
    @translations = []
    @rotations = []
  end

  def serialize
    buffer = [@bone].pack('l<')
    buffer << pack_array(@translations)
    buffer << pack_array(@rotations)
    buffer
  end

  def read spine, key, value
    @bone = spine.find_bone_index key
    read_array(spine, value, KeyFrame::Translation, @translations, 'translate')
    read_array(spine, value, KeyFrame::Rotation, @rotations, 'rotate')
  end

  private

  def pack_array array
    buffer = [array.count].pack('L<')
    buffer << array.map(&:serialize).reduce(:+) unless array.empty?
    buffer
  end

  def read_array spine, object, klass, array, key
    return if object[key].nil?
    object[key].each do |o|
      k = klass.new
      k.read spine, o
      array << k
    end
  end

end