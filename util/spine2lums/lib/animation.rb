require_relative 'bone_animation'
require_relative 'ik_animation'
require_relative 'keyframe/event'

class Animation

  def initialize
    @bone_animations = []
    @ik_animations = []
    @event_animations = []
  end

  def serialize
  end

  def read spine, key, value
    @name = key
    read_bones value['bones']
    read_iks value['ik']
    read_events value['events']
  end

  private

  def read_bones bones
    return if bones.nil?
    bones.each do |k, v|
      b = BoneAnimation.new
      b.read k, v
      @bone_animations << b
    end
  end

  def read_iks iks
    return if iks.nil?
    iks.each do |k, v|
      ik = IkAnimation.new
      ik.read k, v
      @ik_animations << ik
    end
  end

  def read_events events
    return if events.nil?
    events.each do |o|
      event = KeyFrame::Event.new
      event.read o
      @event_animations << event
    end
  end

end