
f_init = open("out.data","r")
f_conv = open("out.convert","w")


for l_init in f_init:
    w_init = l_init[:-1].split(" ")
    e_init = int( w_init[0] )
    ss = ""
    for i in range( len(w_init)-1 ):
        ss += w_init[i] + " "
    f_conv.write( ss + "-" + w_init[-1] + "\n" )

f_init.close()
f_conv.close()

