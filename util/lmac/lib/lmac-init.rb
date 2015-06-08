require 'fileutils'

module Lmac
  class InitCmd
    def run!
      if File.exists? './Lmacfile'
        puts "Lmacfile already exists - aborting"
      else
        FileUtils.copy(File.dirname(__FILE__) + '/../templates/Lmacfile.txt', './Lmacfile')
        puts "Created Lmacfile"
      end
    end
  end
end
