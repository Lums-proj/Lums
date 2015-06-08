require 'template'

module Action
  module New
    def self.run! name
      if Dir.exists? name
        puts "Project #{name} already exists"
        exit 1 
      end
      Dir.mkdir name
      Dir.chdir name
      puts "Creating project #{name}..."
      t = Template.new
      t.run! :app, name: name
      `lmac init`
    end
  end
end