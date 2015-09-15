class Ik

  attr_reader :name

  def initialize
    @bones = []
  end

  def serialize
    [@bones[0], @bones[1], @target, @bendPositive ? 1 : 0].pack('l<l<L<C')
  end

  def read spine, object
    @name = object['name']
    @bones << spine.find_bone_index(object['bones'][0])
    @bones << spine.find_bone_index(object['bones'][1])
    @target = spine.find_bone_index(object['target'])
    @bend_positive = object['bendPositive'].nil? ? true : object['bendPositive']
  end

end