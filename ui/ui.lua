local ui = {}

function ui.makeButton(x, y, width, height, label, onclick)
	local released = 1
	local pressed = 2

	local button = {}
	button.x = x
	button.y = y
	button.width = width
	button.height = height
	button.label = label
	button.state = released

	button.update = function(dt)
	end

	button.draw = function()
		if button.state == released then
			love.graphics.setColor(0, 0, 0)
			love.graphics.rectangle("fill", button.x - button.width / 2.0, button.y - button.height / 2.0, button.width, button.height)

			love.graphics.setColor(0.7, 0.7, 0.7)
			love.graphics.rectangle("fill", button.x - button.width / 2.0, button.y + button.height / 2.0, width, 8)

			love.graphics.setColor(1, 1, 1)
			local text = love.graphics.newText(fonts["Romulus"], button.label)
			love.graphics.draw(text, math.floor(button.x - text:getWidth() / 2), math.floor(button.y - text:getHeight() / 2))

		else
			love.graphics.setColor(0, 0, 0)
			love.graphics.rectangle("fill", button.x - button.width / 2.0, button.y - button.height / 2.0 + 8, button.width, button.height)

			love.graphics.setColor(0.7, 0.7, 0.7)
			love.graphics.rectangle("fill", button.x - button.width / 2.0, button.y - button.height / 2.0, width, 8)

			love.graphics.setColor(1, 1, 1)
			local text = love.graphics.newText(fonts["Romulus"], button.label)
			love.graphics.draw(text, math.floor(button.x - text:getWidth() / 2), math.floor(button.y - text:getHeight() / 2 + 8))
		end
	end

	button.mousepressed = function(x, y, mouseButton, istouch, presses)
		if mouseButton == 1
		and math.abs(x - button.x) <= button.width / 2.0
		and math.abs(y - button.y) <= button.height / 2.0 then
			button.state = pressed
			soundEffects["button_click"]:play()
		end
	end

	button.mousereleased = function(x, y, mouseButton, istouch)
		if mouseButton == 1
		and button.state == pressed then
			button.state = released
			if math.abs(x - button.x) <= button.width / 2.0
			and math.abs(y - button.y) <= button.height / 2.0 then
				if onclick ~= nil then
					onclick()
				end
			end
		end
	end

	return button
end

function ui.makeCard(x, y, image)
	local node = {}
	node.x = x
	node.y = y
	node.image = image
	node.player = player
	node.tank = {}
	node.tank.attack = 1
	node.tank.life = 1
	node.tank.range = 1
	node.tank.speed = 1

	node.children = {}

	node.update = function(dt)
	end

	local width = 128
	local height = 225
	node.draw = function()
		love.graphics.setColor(0, 0, 0)
		love.graphics.rectangle("line", x - width / 2.0, y - height / 2.0, width, height)

		local quad = getQuad("tank")
		love.graphics.setColor(1, 1, 1)
		love.graphics.draw(atlas, quad, x - width / 2.0 + 8, y - height / 2.0, 0.0, 3.5, 3.5)

		love.graphics.setColor(0, 0, 0)
		love.graphics.line(x - width / 2.0, y, x + width / 2.0, y)
	end

	return node
end

return ui
