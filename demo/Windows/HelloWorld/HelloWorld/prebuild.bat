CL /P /EP hello_world.xc
java -Xss6M -jar ../../../../ableC.jar hello_world.i --skip-cpp --show-lifted-pp > hello_world.generated.h
