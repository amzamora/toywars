local screen = {}
screen.children = {}

local ui = require("ui.ui")

function screen.load()
	screen.children = {}
	table.insert(screen.children, ui.Button(0, 0, 180, 80, "PLAY", function()
			loadScreen("armybuildingscreen")
		end))
	table.insert(screen.children, ui.Button(0, -110, 180, 80,"QUIT"))
end

function screen.update(dt)
end

function screen.draw()
end

return screen
