require 'json'

class Player < Struct.new(:x,:y); end

class Level
  attr_accessor :entities, :map

  def initialize(e, m)
    @entities = e
    @map = m
  end
end


class LevelLoader
  attr_accessor :file

  def initialize()
  end

  def loadLevel(path)
    data = JSON.parse(File.read(path))
    Level.new(Player.new(data["posX"],data["posY"]),data["map"])
  end
end
