require File.dirname(__FILE__) + '/compiler'

module Lmac
  class RunCmd
    def run!
      unless File.exists? './Lmacfile'
        puts "No Lmacfile in current working directory"
        return
      end
      file = File.read './Lmacfile'
      compiler = ::Lmac::Compiler.new
      compiler.instance_eval file
      compiler.run!
    end
  end
end