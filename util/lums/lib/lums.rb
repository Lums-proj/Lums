require 'new'
require 'build'
require 'run'

def main args
  if args.empty?
    usage
    exit
  else
    case args.shift
    when 'new'
      command_new args
    when 'build', 'b'
      build
    when 'run', 'r'
      build
      run
    else
      puts "Unknown action"
      exit 1
    end
  end
end

def usage
  puts "usage: lums <action> [params ...]"
  puts
  puts "See `lums help` for more informations"
end

def build
  Action::build
end

def run
  Action::run
end

def command_new args
  if args.size != 1
    puts "usage: lums new <name>"
  else
    Action::New.run! args.first
  end
end

main ARGV
