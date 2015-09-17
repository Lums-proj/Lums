require_relative 'bone_animation'
require_relative 'ik_animation'
require_relative 'slot_animation'
require_relative 'keyframe/event'

class Animation

  def initialize
    @bone_animations = []
    @ik_animations = []
    @event_animations = []
    @slot_animations = []
  end

  def serialize
    buffer = [@name.size, @name].pack('L<a*')
    buffer << serialize_array(@bone_animations)
    buffer << serialize_array(@ik_animations)
    buffer << serialize_array(@event_animations)
    buffer << serialize_array(@slot_animations)
  end

  def read spine, key, value
    @name = key
    read_bones spine, value['bones']
    read_iks spine, value['ik']
    read_events spine, value['events']
    read_slots spine, value['slots']
  end

  private

  def read_bones spine, bones
    return if bones.nil?
    bones.each do |k, v|
      b = BoneAnimation.new
      b.read spine, k, v
      @bone_animations << b
    end
  end

  def read_iks spine, iks
    return if iks.nil?
    iks.each do |k, v|
      ik = IkAnimation.new
      ik.read spine, k, v
      @ik_animations << ik
    end
  end

  def read_events spine, events
    return if events.nil?
    events.each do |o|
      event = KeyFrame::Event.new
      event.read spine, o
      @event_animations << event
    end
  end

  def read_slots spine, slots
    return if slots.nil?
    slots.each do |k, v|
      slot = SlotAnimation.new
      slot.read spine, k, v
      @slot_animations << slot
    end
  end

  def serialize_array array
    buffer = [array.count].pack('L<')
    buffer << array.map(&:serialize).reduce(:+) unless array.empty?
    buffer
  end

end