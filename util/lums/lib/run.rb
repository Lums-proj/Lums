module Action
  def self.run
    name = File.basename(Dir.pwd).downcase.tr(' ', '')
    system("build/#{name}")
  end
end
