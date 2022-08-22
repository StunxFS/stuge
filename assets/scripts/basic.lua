log.info("Hello World!")

if GAME_LANG == GL_English then
    log.info("GL_English")
end

SharedValues.set(0, "This is a simple string =D")
if SharedValues.is(SVK_STRING, 0) then
    log.info(SharedValues.get(0))
end
