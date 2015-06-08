module Action
  def self.build
    Dir.mkdir 'build' unless File.exists? 'build'
    Dir.chdir 'build'
    system 'cmake', '..', '-G', 'Ninja'
    system 'ninja'
    Dir.chdir '..'
  end
end