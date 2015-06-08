require 'new'

def main args
  if args.empty?
    usage
    exit
  else
    case args.shift
    when 'new'
      command_new args
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

def command_new args
  if args.size != 1
    puts "usage: lums new <name>"
  else
    Action::New.run! args.first
  end
end

main ARGV
