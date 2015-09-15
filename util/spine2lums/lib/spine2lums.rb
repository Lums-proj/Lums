require 'ap'
require 'json'
require_relative 'bone'
require_relative 'animation'
require_relative 'ik'

class Spine2Lums

  attr_reader :bones

  def initialize
    @bones = []
    @animations = []
    @iks = []
  end

  def run! spine_file
    data = JSON.parse(File.read spine_file)
    read data
    ap @bones
    ap @animations
    ap @iks
  end

  def serialize
  end

  def read object
    read_bones object['bones']
    read_iks object['ik']
    read_animations object['animations']
  end

  def read_bones bones
    bones.each do |o|
      bone = Bone.new
      bone.read self, o
      @bones << bone
    end
  end

  def read_iks iks
    iks.each do |o|
      ik = Ik.new
      ik.read self, o
      @iks << ik
    end
  end


  def read_animations animations
    animations.each do |k, v|
      animation = Animation.new
      animation.read self, k, v
      @animations << animation
    end
  end

  def find_bone_index name
    @bones.find_index {|b| name == b.name} || -1
  end

end