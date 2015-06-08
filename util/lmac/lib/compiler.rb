require File.dirname(__FILE__) + '/module'

module Lmac
  class Compiler
    def initialize
      @use = []
    end

    def run!
      
    end

    def modules path
      @module_path = path
    end

    def use mod, options = {}
      @modules << ::Lmac::Module.new(self, options)
    end

    def source path
      @source = path
    end

    def dest path
      @dest = path
    end

    def manifest path, options = {}
      @manifest = [path, options]
    end
  end
end