module Lmac
  class HelpCmd
    def run!
      puts "Usage: lmac <action>"
      puts
      puts "Actions:"
      puts "    help             show this message"
      puts "    run              run lmac"
      puts "    init             creates an Lmacfile"
      puts
      puts "lmac, as well as the Lums library, is distributed under MIT license"
      puts "Made by the Lums Team - 2015"
    end
  end
end
