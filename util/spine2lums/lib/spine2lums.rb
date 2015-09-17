require 'json'
require_relative 'bone'
require_relative 'animation'
require_relative 'ik'
require_relative 'texture'
require_relative 'attachment'
require_relative 'slot'

class Spine2Lums

  attr_reader :bones, :slots

  def initialize
    @bones = []
    @iks = []
    @textures = []
    @attachments = []
    @slots = []
    @animations = []
  end

  def run! spine_file, atlas_file, spine_output, atlas_output
    read_atlas File.read atlas_file
    data = JSON.parse(File.read spine_file)
    read data
    atlas_buffer = serialize_atlas
    File.write atlas_output, atlas_buffer
    spine_buffer = serialize
    File.write spine_output, spine_buffer
  end

  def serialize
    buffer = ""
    buffer << serialize_array(@bones)
    buffer << serialize_array(@slots)
    buffer << serialize_array(@attachments)
    buffer << serialize_array(@iks)
    buffer << serialize_array(@animations)
  end

  def serialize_atlas
    serialize_array @textures
  end

  def read object
    read_bones object['bones']
    read_iks object['ik']
    read_slots object['slots']
    read_attachments object['skins']
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

  def read_attachments attachments
    skin = {}
    attachments.each {|k, v| skin.merge! v}
    skin.each do |bone, slot|
      slot.each do |k, v|
        if v['type'].nil? || v['type'] == 'region'
          att = Attachment.new
          att.read self, bone, k, v
          @attachments << att
        end
      end
    end
  end

  def read_slots slots
    slots.each do |s|
      slot = Slot.new
      slot.read self, s
      @slots << slot
    end
  end

  def read_animations animations
    animations.each do |k, v|
      animation = Animation.new
      animation.read self, k, v
      @animations << animation
    end
  end

  def read_atlas atlas
    array = atlas.split "\n"
    header = array.shift 6
    size = header[2].split(' ')[1].split(',').map(&:to_i)
    array.each_slice 7 do |b|
      texture = Texture.new
      texture.read b, size   
      @textures << texture
    end
  end

  def find_bone_index name
    @bones.find_index {|b| name == b.name} || -1
  end

  def find_texture_index name
    @textures.find_index {|t| name == t.name} || -1
  end

  def find_attachment_index name
    @attachments.find_index {|t| name == t.name} || -1
  end

  def find_slot_index name
    @slots.find_index {|t| name == t.name} || -1
  end

  def find_ik_index name
    @iks.find_index {|t| name == t.name} || -1
  end

  private

  def serialize_array array
    buffer = [array.count].pack('L<')
    buffer << array.map{|o| o.serialize(self) }.reduce(:+)
    buffer
  end

end