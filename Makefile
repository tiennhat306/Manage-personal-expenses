#define
OBJ = main.o DateTime.o Vector.o GiaoDich.o TietKiem.o VayNo.o NganHang.o Graphic.o User.o QuanLyUser.o QL.o QL_NganHang.o QL_GiaoDich.o QL_VayNo.o QL_TietKiem.o Menu.o
HEADER = DateTime.h Vector.h GiaoDich.h TietKiem.h VayNo.h NganHang.h Graphic.h User.h QuanLyUser.h QL.h QL_NganHang.h QL_GiaoDich.h QL_VayNo.h QL_TietKiem.h Menu.h
CPP = DateTime.cpp Vector.cpp GiaoDich.cpp TietKiem.cpp VayNo.cpp NganHang.cpp Graphic.cpp User.cpp QuanLyUser.cpp QL.cpp QL_NganHang.cpp QL_GiaoDich.cpp QL_VayNo.cpp QL_TietKiem.cpp Menu.cpp
CC = g++
output: $(OBJ)
	$(CC) $(OBJ) -o output 
main.o: main.cpp
	$(CC) -c main.cpp
Vector.o: Vector.cpp Vector.h
	$(CC) -c Vector.cpp
GiaoDich.o: GiaoDich.cpp GiaoDich.h
	$(CC) -c GiaoDich.cpp
DateTime.o: DateTime.cpp DateTime.h
	$(CC) -c DateTime.cpp
TietKiem.o: TietKiem.cpp TietKiem.h
	$(CC) -c TietKiem.cpp
VayNo.o: VayNo.cpp VayNo.h
	$(CC) -c VayNo.cpp
NganHang.o: NganHang.cpp NganHang.h
	$(CC) -c NganHang.cpp

Graphic.o: Graphic.cpp Graphic.h
	g++ -c Graphic.cpp
User.o: User.cpp User.h
	g++ -c User.cpp
QuanLyUser.o: QuanLyUser.cpp QuanLyUser.h
	g++ -c QuanLyUser.cpp

QL.o: QL.cpp QL.h
	$(CC) -c QL.cpp
QL_NganHang.o: QL_NganHang.cpp QL_NganHang.h
	$(CC) -c QL_NganHang.cpp
QL_GiaoDich.o: QL_GiaoDich.cpp QL_GiaoDich.h
	$(CC) -c QL_GiaoDich.cpp
QL_VayNo.o: QL_VayNo.cpp QL_VayNo.h
	$(CC) -c QL_VayNo.cpp
QL_TietKiem.o: QL_TietKiem.cpp QL_TietKiem.h
	$(CC) -c QL_TietKiem.cpp
Menu.o: Menu.cpp Menu.h
	$(CC) -c Menu.cpp
# login.o: login.cpp
# 	g++ -c login.cpp


# file.o: $(OBJ) $(HEADER)
# 	$(CC) -c $(CPP)
clean:
	del *.o output