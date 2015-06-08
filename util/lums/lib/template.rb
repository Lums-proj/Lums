require 'colorize'
require 'erb'

class Template
  STATUS = {
      created: 'created'.green,
      untouched: 'untouched'.black,
      replaced: 'replaced'.yellow
  }

  def run! template, params = {}
    @template = template.to_s
    @params = params
    @dir = Dir.pwd
    @template_dir = File.dirname(__FILE__) + '/../templates/' + @template
    Dir.chdir @template_dir
    files = Dir['**/*']
    Dir.chdir @dir
    files.each {|f| templatize f}
  end

  def templatize file
    status = nil
    exists = File.exists? file
    directory = File.directory? @template_dir + '/' + file
    if exists
      if directory
        status = :untouched
      else
        status = :replaced
      end
    else
      status = :created
    end
    printf "    %-20s %s\n", STATUS[status], file.white
    if directory && status == :created
      Dir.mkdir file
    else
      erb = ERB.new(File.read(@template_dir + '/' + file))
      File.write(file, erb.result(binding))
    end
  end
end