NAME = midi2

# Installed by the Faust distribution's (../../faustmasterdev/) "sudo make install":
F2CA = /usr/local/bin/faust2caqt
NVOICES = 8

# For building a Core-Audio QT4 app on the Mac:
# sudo port install qt4-mac
# sudo ln -s /opt/local/libexec/qt4/bin/qmake /usr/local/bin/qmake

open o: $(NAME).app
	-killall $(NAME)
	open $(NAME).app

$(NAME).app ca: $(NAME).dsp 
	$(F2CA) -nvoices $(NVOICES) -midi $(NAME).dsp
	-killall $(NAME)
	open $(NAME).app

f2iosapp ia:
	faust2ios -xcode -xcodeproj -nvoices $(NVOICES) -midi $(NAME).dsp
	open $(NAME)/iOS.xcodeproj


DATE = `date +%Y-%m-%d-%H:%M:%S`

td:
	echo ToDayIs-$(DATE)

t:
	faust $(NAME).dsp

d:
	faust2firefox $(NAME).dsp

clean tclean:
	-/bin/rm -rf faust.* $(NAME) $(NAME).app $(NAME) $(NAME)-svg 
	-killall $(NAME) 
	-/bin/rm -rf faust.* $(NAME) $(NAME).app $(NAME) $(NAME)-svg


# ? Images.xcassets
