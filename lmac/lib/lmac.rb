require File.dirname(__FILE__) + '/lmac-init'
require File.dirname(__FILE__) + '/lmac-help'

module Lmac
  class Main
    ACTIONS = {
      'help' => ::Lmac::HelpCmd,
      'init' => ::Lmac::InitCmd
    }

    def run! arg
      arg ||= 'run'
      action = ACTIONS[arg]
      if action.nil?
        puts "Invalid action: #{arg}"
      else
        action.new.run!
      end
    end
  end
end

Lmac::Main.new.run! ARGV.first
