class EventManager
  attr_accessor :subs;

  def initialize()
    @subs = {}
  end

  def subscribe(sub, type)
    if @subs.has_key? type
      @subs[type] << sub
    else
      @subs[type] = [sub]
    end
  end

  def unsubscribe(sub, type)
    if @subs.has_key? type
      @subs[type] -= Array(sub)
      true
    else
      false
    end
  end

  def fire(event)
    if @subs.has_key? event.class
      puts event.class
      (@subs[event.class] || []).each{ |sub|
        sub.notify(event);
      }
    end
  end
end

class GameObject
  attr_accessor :x, :y
  def initialize(x,y)
    @x = x
    @y = y
  end

  def notify(event)
  end
end

class Enemy < GameObject
  def initialize(x,y)
    super(x,y)
  end

  def notify(event)
    case event.class.to_s
    when "PlayerShootEvent"
      puts "somebody done shot a gun from #{event.data.to_s}"
    end
  end
end

class Event
  attr_accessor :data

  def initialize(data)
    @data = data
  end
end

class PlayerShootEvent < Event
  def initialize(data)
    super(data)
  end
end

em = EventManager.new
