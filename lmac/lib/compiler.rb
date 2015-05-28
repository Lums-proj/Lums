module Lmac
  class Compiler
    def initialize
      @use = []
    end

    def run!
      p self
    end

    def modules path
      @modules = path
    end

    def use mod, options = {}
      @use << [mod, options]
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