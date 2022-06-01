.PHONY: clean All

All:
	@echo "----------Building project:[ Vertical - Debug ]----------"
	@cd "Vertical" && "$(MAKE)" -f  "Vertical.mk"
clean:
	@echo "----------Cleaning project:[ Vertical - Debug ]----------"
	@cd "Vertical" && "$(MAKE)" -f  "Vertical.mk" clean
