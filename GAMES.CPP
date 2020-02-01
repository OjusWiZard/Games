#include <fstream.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define  SPADE   4
#define  DIAMOND 3
#define  CLUB    2
#define  HEART   1
#define  DIAG    sqrt(pow(getmaxx(),2)+pow(getmaxy(),2))


class Player
{
	public:
	int s[3], n[3], win;

	void card( int x, int y, int s, int n );

	void shape( int& x, int& y, int& s );

	void num( int& x, int& y, int& n );
};

Player p1, p2;

struct Highscore
{
	int high;
};
Highscore TP, Tunnel;

fstream hi;

void SelectGame();

void initiate();

void TunnelIntro();

void TunnelGame();

void TunnelMenu();

void HTPTunnel();

void bike();

void TunnelResult( int& r );

void Initialize();

void distribute();

void countdown();

void HTPTP();

void TPGame();

void TPMenu();

void TPResult();

void* Bike;

int tunnel( int& ang, int& dis, int& pos );

int greatest( int& a, int& b, int& c );

int greater( int& a, int& b, int& c );

int great( int& a, int& b, int& c );

int compare
( int& sa0, int& sa1, int& sa2,
  int& na0, int& na1, int& na2,
  int& sb0, int& sb1, int& sb2,
  int& nb0, int& nb1, int& nb2
);

int p00x, p01x, p02x,
p10x, p11x, p12x,
p00y, p01y, p02y,
p10y, p11y, p12y, sco;


void main()
{
	clrscr();
	initiate();
	SelectGame();
	hi.close();
	cleardevice();
	closegraph();
}


void initiate()
{
	int gd = VGA, gm = VGAHI;
	initgraph( &gd, &gm, "C:\\TurboC3\\BGI\\" );
	setbkcolor( WHITE );
	p00x = 3*getmaxx()/8;
	p01x = getmaxx()/2;
	p02x = 5*getmaxx()/8;
	p10x = 3*getmaxx()/8;
	p11x = getmaxx()/2;
	p12x = 5*getmaxx()/8;
	p00y = getmaxy()/4;
	p01y = getmaxy()/4;
	p02y = getmaxy()/4;
	p10y = 3*getmaxy()/4;
	p11y = 3*getmaxy()/4;
	p12y = 3*getmaxy()/4;
	hi.open( "HIGHSCR.OJ", ios::in|ios::out|ios::binary|ios::nocreate );
	if( !hi )
	{
		hi.open( "HIGHSCR.OJ", ios::in|ios::out|ios::binary );
		hi.seekp( 0 );
		TP.high = 0;
		hi.write( (char*)&TP, sizeof( TP ) );
		hi.seekp( 4 );
		Tunnel.high = 0;
		hi.write( (char*)&Tunnel, sizeof( Tunnel ) );
	}
}


void SelectGame()
{
	int hitp, hitu, input, option = 1;
	char h1[3], h2[3];
	randomize();
	while( input!=27 )
	{
		hi.seekg( 0 );
		hi.read( (char*)&TP, sizeof( TP ) );
		hitp = TP.high;
		hi.seekg( 4 );
		hi.read( (char*)&Tunnel, sizeof( Tunnel ) );
		hitu = Tunnel.high;
		settextstyle( GOTHIC_FONT, 0, 7 );
		settextjustify( CENTER_TEXT, CENTER_TEXT );
		setlinestyle( CENTER_LINE, 0, THICK_WIDTH );
		setfillstyle( SOLID_FILL, DARKGRAY );
		bar( getmaxx()/2, 0, getmaxx(), getmaxx() );
		setcolor( WHITE );
		outtextxy( 3*getmaxx()/4, getmaxy()/2, "Tunnel" );
		settextstyle( DEFAULT_FONT, 0, 2 );
		outtextxy( 3*getmaxx()/4-25, getmaxy()-40, "Highscore :" );
		outtextxy( 3*getmaxx()/4+85, getmaxy()-40, itoa( hitu, h1, 10 ) );
		setcolor( DARKGRAY );
		settextstyle( GOTHIC_FONT, 0, 7 );
		outtextxy( getmaxx()/4, getmaxy()/2, "Teen Patti" );
		settextstyle( DEFAULT_FONT, 0, 2 );
		outtextxy( getmaxx()/4-25, getmaxy()-40, "Highscore :" );
		outtextxy( getmaxx()/4+85, getmaxy()-40, itoa( hitp, h2, 10 ) );
		switch( option )
		{
			case 1:
			while( !kbhit() )
			{
				setcolor( random( 16 ) );
				rectangle( getmaxx()/4-140,
						   getmaxy()/2-30,
						   getmaxx()/4+140,
						   getmaxy()/2+50 );
				delay( 100 );
			}
			cleardevice();
			break;
			case 2:
			while( !kbhit() )
			{
				setcolor( random( 16 ) );
				rectangle( 3*getmaxx()/4-140,
						   getmaxy()/2-30,
						   3*getmaxx()/4+140,
						   getmaxy()/2+50 );
				delay( 100 );
			}
			cleardevice();
			break;
		}
		graphdefaults();
		setbkcolor( WHITE );
		input = getch();
		if( ( input==75 )||( input==77 ) )
		{
			switch( option )
			{
				case 1:
				option = 2;
				break;
				case 2:
				option = 1;
				break;
			}
		}
		if( input==13 )
		{
			switch( option )
			{
				case 2:
				TunnelIntro();
				TunnelMenu();
				break;
				case 1:
				TPMenu();
				break;
			}
		}
		cleardevice();
	}
}


void TunnelIntro()
{
	int f, k;
	cleardevice();
	setcolor( DARKGRAY );
	sound( 700 );
	delay( 50 );
	sound( 1000 );
	moveto( 30, 50+0*25 );
	outtext( "In This Game, You Are Riding A Bike At A Lightning Speed." );
	delay( 100 );
	nosound();
	k = getch();
	if( k==27 )
	{
		goto End;
	}
	getch();
	moveto( 30, 50+1*25 );
	sound( 1000 );
	outtext( "There Was No Stress In Your Life." );
	delay( 100 );
	nosound();
	k = getch();
	if( k==27 )
	{
		goto End;
	}
	getch();
	moveto( 30, 50+3*25 );
	outtext( "But Now, You Are In A Huge Warp Tunnel." );
	sound( 50 );
	delay( 100 );
	nosound();
	delay( 100 );
	sound( 50 );
	delay( 100 );
	nosound();
	delay( 100 );
	sound( 50 );
	delay( 100 );
	nosound();
	k = getch();
	if( k==27 )
	{
		goto End;
	}
	getch();
	moveto( 30, 50+4*25 );
	sound( 60 );
	outtext( "A Tunnel Full Of Holes," );
	delay( 60 );
	nosound();
	moveto( 30, 50+5*25 );
	outtext( "A Tunnel With Its Own Gravity," );
	moveto( 30, 50+6*25 );
	outtext( "A Tunnel Whose Light Can Penetrate Almost Anything." );
	k = getch();
	if( k==27 )
	{
		goto End;
	}
	getch();
	moveto( 30, 50+8*25 );
	sound( 1000 );
	delay( 60 );
	outtext( "The Game is Simple." );
	nosound();
	k = getch();
	if( k==27 )
	{
		goto End;
	}
	getch();
	moveto( 30, 50+9*25 );
	sound( 400 );
	delay( 60 );
	outtext( "You Can't Turn Around." );
	nosound();
	moveto( 30, 50+10*25 );
	k = getch();
	if( k==27 )
	{
		goto End;
	}
	getch();
	moveto( 30, 50+11*25 );
	sound( 1000 );
	delay( 60 );
	outtext( "Just Travel As Far As You Can & Score As Much As You Can." );
	nosound();
	k = getch();
	if( k==27 )
	{
		goto End;
	}
	getch();
	moveto( 30, 50+13*25 );
	outtext( "And Remember..." );
	k = getch();
	if( k==27 )
	{
		goto End;
	}
	getch();
	moveto( 30, 50+14*25 );
	outtext( "Your Stress Starts From Now !" );
	for( f = 0; f<=2000; f += 50 )
	{
		sound( 2000-f );
		delay( 10 );
	}
	nosound();
	getch();
End:
	cleardevice();
}


void TunnelMenu()
{
	int op = 1, in, ang = 0;
	while( in!=27 )
	{
		sound( 1500 );
		sco = 0;
		setbkcolor( WHITE );
		setcolor( LIGHTGRAY );
		for( int i = 0; i<10; i++, ang += 36, ang = ang%360 )
		{
			line( getmaxx()/2+10*cos( ang*M_PI/180 ),
				  getmaxy()/2-10*sin( ang*M_PI/180 ),
				  getmaxx()/2+DIAG*cos( ang*M_PI/180 )/2,
				  getmaxy()/2-DIAG*sin( ang*M_PI/180 )/2 );
		}
		setcolor( RED );
		settextstyle( GOTHIC_FONT, 0, 10 );
		settextjustify( CENTER_TEXT, CENTER_TEXT );
		outtextxy( getmaxx()/2, getmaxy()/2-150, "Tunnel" );
		settextstyle( TRIPLEX_FONT, 0, 4 );
		setcolor( BLUE );
		settextjustify( 0, 0 );
		outtextxy( getmaxx()/2-100, getmaxx()/2-80, "Start Game" );
		outtextxy( getmaxx()/2-100, getmaxx()/2-30, "How To Play" );
		outtextxy( getmaxx()/2-100, getmaxx()/2+20, "Select Game" );
		outtextxy( getmaxx()/2-100, getmaxx()/2+70, "Exit" );
		delay( 10 );
		nosound();
		switch( op )
		{
			case 1:
			outtextxy( getmaxx()/2-150, getmaxy()/2, "->" );
			break;
			case 2:
			outtextxy( getmaxx()/2-150, getmaxy()/2+50, "->" );
			break;
			case 3:
			outtextxy( getmaxx()/2-150, getmaxy()/2+100, "->" );
			break;
			case 4:
			outtextxy( getmaxx()/2-150, getmaxy()/2+150, "->" );
			break;
		}
		in = getch();
		switch( in )
		{
			case 72:
			if( op==1 ) op = 4;
			else op--;
			break;
			case 80:
			if( op==4 ) op = 1;
			else op++;
			break;
			case 13:
			switch( op )
			{
				case 1:
				TunnelGame();
				break;
				case 2:
				HTPTunnel();
				break;
				case 4:
				cleardevice();
				closegraph();
				exit( 0 );
				break;
				case 3:
				return;
			};
			break;
		}
		cleardevice();
	}
}


void TunnelGame()
{
	int i, j, in, ang = 0, dis, pos, r = 1;
	char sc[4];
	graphdefaults();
	setbkcolor( WHITE );
	settextstyle( 5, 0, 0 );
	setcolor( BROWN );
	setusercharsize( 9, 4, 9, 4 );
	char s[16] = { 'S', 't', 'a', 'r', 't', ' ', 'T', 'h', 'e', ' ', 'g', 'a', 'm', 'e', ' ', '?' },
		t[16];
	for( i = 0; i<16; i++, delay( 100 ) )
	{
		cleardevice();
		for( j = 0; j<=i; j++ )
		{
			t[j] = s[j];
		}
		t[i+1] = '\0';
		outtextxy( getmaxx()/2-285, getmaxy()/2-100, t );
		sound( 400+pow( 20*( 10+i ), i%2 ) );
	}
	settextstyle( 8, 0, 2 );
	setcolor( RED );
	nosound();
	delay( 500 );
	sound( 1000 );
	outtextxy( getmaxx()/2-40, getmaxy()/2, "(y/n)" );
	delay( 50 );
	nosound();
a:
	switch( getch() )
	{
		case 'y':
		break;
		case 'Y':
		break;
		case 'n':
		return;
		case 'N':
		return;
		default:
		goto a;
	}
	bike();
	countdown();
	delay( 500 );
	randomize();
	while( ( sco!=101 )&&( r!=0 ) )
	{
		if( sco>=50 )
		{
			setbkcolor( WHITE );
		}
		else
		{
			setbkcolor( BLACK );
		}
		pos = random( 10 )+1;
		for( dis = 8; dis<DIAG/32+5; dis++ )
		{
			if( kbhit() )
			{
				in = getch();
			}
			switch( in )
			{
				case 75:
				ang += 6;
				break;
				case 77:
				ang -= 6;
				break;
			}
			sound( ( random( 4 )+2 )*pow( 15*dis, dis%2 )/2 );
			if( ( !dis%4 )||random( 2 ) )
			{
				nosound();
			}
			cleardevice();
			if( tunnel( ang, dis, pos ) )
			{
				r = 0;
				goto Result;
			}
			outtextxy( getmaxx()-50, 5, itoa( sco, sc, 10 ) );
			delay( 100-sco );
		}
		sco++;
	}
Result:
	nosound();
	i = getch();
	if( ( i==72 )||( i==75 )||( i==77 )||( i==80 ) )
	{
		getch();
	}
	Tunnel.high = sco;
	TunnelResult( r );
}


int tunnel( int& ang, int& dis, int& pos )
{
	int dis1, dis2, h[10];
	dis1 = ( dis*dis*dis*DIAG*DIAG )/( 200*( ( dis*dis )+( ( DIAG*DIAG )/4 ) ) );
	dis2 = ( ( dis+2 )*( dis+2 )*( dis+2 )*DIAG*DIAG )/
		( 200*( ( ( dis+2 )*( dis+2 ) )+( ( DIAG*DIAG )/4 ) ) );
	setcolor( LIGHTGRAY );
	circle( getmaxx()/2, getmaxy()/2, dis2 );
	for( int i = 0; i<10; i++, ang += 36, ang = ang%360 )
	{
		line( getmaxx()/2+10*cos( ang*M_PI/180 ),
			  getmaxy()/2-10*sin( ang*M_PI/180 ),
			  getmaxx()/2+DIAG*cos( ang*M_PI/180 )/2,
			  getmaxy()/2-DIAG*sin( ang*M_PI/180 )/2 );
	}
	setcolor( LIGHTRED );
	line( getmaxx()/2+dis1*cos( ( 36*pos+ang )*M_PI/180 ),
		  getmaxy()/2-dis1*sin( ( 36*pos+ang )*M_PI/180 ),
		  getmaxx()/2+DIAG*cos( ( 36*pos+ang )*M_PI/180 ),
		  getmaxy()/2-DIAG*sin( ( 36*pos+ang )*M_PI/180 ) );
	line( getmaxx()/2+dis1*cos( ( 36*( pos+1 )+ang )*M_PI/180 ),
		  getmaxy()/2-dis1*sin( ( 36*( pos+1 )+ang )*M_PI/180 ),
		  getmaxx()/2+DIAG*cos( ( 36*( pos+1 )+ang )*M_PI/180 ),
		  getmaxy()/2-DIAG*sin( ( 36*( pos+1 )+ang )*M_PI/180 ) );
	setfillstyle( 10, BROWN );
	h[0] = getmaxx()/2+dis1*cos( ( 36*pos+ang )*M_PI/180 );
	h[1] = getmaxy()/2-dis1*sin( ( 36*pos+ang )*M_PI/180 );
	h[2] = getmaxx()/2+dis1*cos( ( 36*( pos+1 )+ang )*M_PI/180 );
	h[3] = getmaxy()/2-dis1*sin( ( 36*( pos+1 )+ang )*M_PI/180 );
	h[4] = getmaxx()/2+dis2*cos( ( 36*pos+ang )*M_PI/180 );
	h[5] = getmaxy()/2-dis2*sin( ( 36*pos+ang )*M_PI/180 );
	h[6] = getmaxx()/2+dis2*cos( ( 36*( pos+1 )+ang )*M_PI/180 );
	h[7] = getmaxy()/2-dis2*sin( ( 36*( pos+1 )+ang )*M_PI/180 );
	h[8] = getmaxx()/2+dis1*cos( ( 36*pos+ang )*M_PI/180 );
	h[9] = getmaxy()/2-dis1*sin( ( 36*pos+ang )*M_PI/180 );
	fillpoly( 5, h );
	setcolor( BLUE );
	rectangle( getmaxx()-120, 0, getmaxx(), 15 );
	settextstyle( 0, 0, 0 );
	outtextxy( getmaxx()-110, 5, "Score = " );
	putimage( getmaxx()/2-55,
			  getmaxy()-110,
			  Bike,
			  XOR_PUT
	);
	line( getmaxx()/2,
		  getmaxy()-50,
		  getmaxx()/2+14*cos( ( 181+sco*180/100 )*M_PI/180 ),
		  getmaxy()-50-8*sin( ( 181+sco*180/100 )*M_PI/180 )
	);
	if( ( ( h[5]>getmaxy()-110 )||
		( h[7]>getmaxy()-110 ) )&&
		  ( h[4]<getmaxx()/2 )&&
		( h[6]>getmaxx()/2 )&&
		( h[1]<getmaxy() )&&
		( h[3]<getmaxy() ) )
	{
		return 1;
	}
	return 0;
}


void HTPTunnel()
{
	sound( 800 );
	delay( 100 );
	nosound();
	delay( 140 );
	sound( 800 );
	delay( 100 );
	nosound();
	delay( 120 );
	cleardevice();
	sound( 750 );
	delay( 80 );
	nosound();
	sound( 1000 );
	setcolor( RED );
	settextstyle( TRIPLEX_FONT, 0, 7 );
	settextjustify( CENTER_TEXT, CENTER_TEXT );
	outtextxy( getmaxx()/2, 50, "How To Play" );
	settextstyle( SIMPLEX_FONT, 0, 1 );
	settextjustify( LEFT_TEXT, LEFT_TEXT );
	setcolor( BLUE );
	moveto( 30, 125+0*25 );
	outtext( "This Tunnel contains 10 Tracks." );
	moveto( 30, 125+1*25 );
	outtext( "Initially, you will be at the Lowest Track." );
	moveto( 30, 125+2*25 );
	outtext( "Any Hole on the Track will make it RED." );
	moveto( 30, 125+3*25 );
	outtext( "Just Dodge them using your arrow keys and go as far as you can." );
	moveto( 30, 125+4*25 );
	outtext( "Your one press will move you (continuously) to the respective side" );
	moveto( 50, 125+5*25 );
	outtext( "until you press another." );
	moveto( 30, 125+6*25 );
	outtext( "Press any key other than <- or -> keys to STOP steering." );
	moveto( 30, 125+7*25 );
	outtext( "There is also a Speedometer Installed in your Bike." );
	moveto( 30, 125+8*25 );
	outtext( "And, The Camera will rotate relative to you." );
	moveto( getmaxx()/2-50, 125+9*25 );
	outtext( "Good Luck !" );
	moveto( getmaxx()/2-50, 125+11*25 );
	setcolor( RED );
	outtext( "ATTENTION !" );
	moveto( 30, 125+12*25 );
	setcolor( LIGHTRED );
	outtext( "The driver of this Game does not support Dynamic Keyboard Input." );
	moveto( 30, 125+13*25 );
	outtext( "So, do NOT hold the keys." );
	delay( 140 );
	nosound();
	getch();
}


void bike()
{
	cleardevice();
	int size;
	setcolor( BROWN );
	ellipse( getmaxx()/2, getmaxy()/2, 0, 180, 15, 30 );
	setcolor( BLUE );
	ellipse( getmaxx()/2, getmaxy()/2+18, 0, 180, 20, 25 );
	setcolor( DARKGRAY );
	rectangle( getmaxx()/2-52,
			   getmaxy()/2+18,
			   getmaxx()/2+52,
			   getmaxy()/2+27 );
	setcolor( MAGENTA );
	ellipse( getmaxx()/2-26, getmaxy()/2+22, 26, 315, 3, 7 );
	ellipse( getmaxx()/2+26, getmaxy()/2+22, 230, 145, 3, 7 );
	ellipse( getmaxx()/2-52, getmaxy()/2+22, 26, 315, 3, 7 );
	ellipse( getmaxx()/2+52, getmaxy()/2+22, 230, 145, 3, 7 );
	ellipse( getmaxx()/2, getmaxy()/2+27, 180, 0, 18, 14 );
	setcolor( BLUE );
	ellipse( getmaxx()/2+12, getmaxy()/2+56, 145, 209, 40, 50 );
	ellipse( getmaxx()/2-12, getmaxy()/2+56, 331, 35, 40, 50 );
	line( getmaxx()/2-22,
		  getmaxy()/2+80,
		  getmaxx()/2+22,
		  getmaxy()/2+80 );
	setcolor( DARKGRAY );
	circle( getmaxx()/2, getmaxy()/2+65, 11 );
	line( getmaxx()/2,
		  getmaxy()/2+62,
		  getmaxx()/2,
		  getmaxy()/2+68 );
	size = imagesize( getmaxx()/2-55,
					  getmaxy()/2-30,
					  getmaxx()/2+55,
					  getmaxy()/2+80 );
	Bike = malloc( size );
	getimage( getmaxx()/2-55,
			  getmaxy()/2-30,
			  getmaxx()/2+55,
			  getmaxy()/2+80,
			  Bike );
}


void TunnelResult( int& r )
{
	int f, preh;
	if( r==1 )
	{
		for( f = 0; f<1000; f++ )
		{
			sound( f+1000*sin( f ) );
			delay( 2 );
		}
	}
	nosound();
	delay( 500 );
	getch();
	cleardevice();
	setcolor( LIGHTGRAY );
	for( int i = 0, ang = 0; i<10; i++, ang += 36, ang = ang%360 )
	{
		line( getmaxx()/2+10*cos( ang*M_PI/180 ),
			  getmaxy()/2-10*sin( ang*M_PI/180 ),
			  getmaxx()/2+DIAG*cos( ang*M_PI/180 )/2,
			  getmaxy()/2-DIAG*sin( ang*M_PI/180 )/2 );
	}
	char sc[4];
	settextstyle( TRIPLEX_FONT, 0, 7 );
	setcolor( RED );
	settextjustify( CENTER_TEXT, CENTER_TEXT );
	outtextxy( getmaxx()/2, 50, "Result" );
	setcolor( BLUE );
	settextstyle( 7, 0, 4 );
	hi.seekg( 4 );
	hi.read( (char*)&Tunnel, sizeof( Tunnel ) );
	preh = Tunnel.high;
	if( r==1 )
	{
		outtextxy( getmaxx()/2, getmaxy()/2-30, "Congratulations !" );
		outtextxy( getmaxx()/2, getmaxy()/2+20, "You Are Now Out Of The Tunnel." );
		outtextxy( getmaxx()/2, getmaxy()/2+70, "Unexpectedly," );
		outtextxy( getmaxx()/2, getmaxy()/2+120, "Warp Tunnel Have Thrown You Out." );
		sound( 500 );
		delay( 60 );
		nosound();
		delay( 20 );
		sound( 800 );
		delay( 300 );
		Tunnel.high = 100;
		hi.seekp( 4 );
		hi.write( (char*)&Tunnel, sizeof( Tunnel ) );
	}
	else
	{
		sound( 600 );
		delay( 70 );
		nosound();
		delay( 350 );
		sound( 600 );
		delay( 70 );
		nosound();
		delay( 350 );
		outtextxy( getmaxx()/2, getmaxy()/2-30, "OOPS !" );
		outtextxy( getmaxx()/2, getmaxy()/2+20, "You Fell Into A Hole." );
		setcolor( RED );
		outtextxy( getmaxx()/2-30, getmaxy()/2+70, "Score :" );
		outtextxy( getmaxx()/2+60, getmaxy()/2+70, itoa( sco, sc, 10 ) );
		for( f = 0; f<600; f++ )
		{
			sound( 600-f );
			delay( 1 );
		}
		if( sco>preh )
		{
			Tunnel.high = sco;
			hi.seekp( 4 );
			hi.write( (char*)&Tunnel, sizeof( Tunnel ) );
		}
	}
	nosound();
	getch();
}


void TPMenu()
{
	setbkcolor( WHITE );
	int op = 1, in = 0, enter;
	while( in!=27 )
	{
		sound( 1500 );
		setcolor( RED );
		settextstyle( GOTHIC_FONT, 0, 10 );
		settextjustify( CENTER_TEXT, CENTER_TEXT );
		outtextxy( getmaxx()/2, getmaxy()/2-150, "Teen Patti" );
		settextstyle( TRIPLEX_FONT, 0, 4 );
		setcolor( BLUE );
		settextjustify( 0, 0 );
		outtextxy( getmaxx()/2-100, getmaxx()/2-80, "Start Game" );
		outtextxy( getmaxx()/2-100, getmaxx()/2-30, "How To Play" );
		outtextxy( getmaxx()/2-100, getmaxx()/2+20, "Select Game" );
		outtextxy( getmaxx()/2-100, getmaxx()/2+70, "Exit" );
		switch( op )
		{
			case 1:
			outtextxy( getmaxx()/2-150, getmaxy()/2, "->" );
			break;
			case 2:
			outtextxy( getmaxx()/2-150, getmaxy()/2+50, "->" );
			break;
			case 3:
			outtextxy( getmaxx()/2-150, getmaxy()/2+100, "->" );
			break;
			case 4:
			outtextxy( getmaxx()/2-150, getmaxy()/2+150, "->" );
			break;
		}
		delay( 10 );
		nosound();
		in = getch();
		switch( in )
		{
			case 72:
			if( op==1 ) op = 4;
			else op--;
			break;
			case 80:
			if( op==4 ) op = 1;
			else op++;
			break;
			case 13:
			enter = 1;
			break;
		}
		if( enter==1 )
		{
			switch( op )
			{
				case 1:
				p1.win = 0;
				p2.win = 0;
				TPGame();
				TPResult();
				break;
				case 2:
				HTPTP();
				break;
				case 4:
				cleardevice();
				closegraph();
				exit( 0 );
				break;
				case 3:
				return;
			}
			enter = 0;
		}
		cleardevice();
	}
}


void TPResult()
{
	char w1[3], w2[3];
	int preh;
	hi.seekg( 0 );
	hi.read( (char*)&TP, sizeof( TP ) );
	preh = TP.high;
	cleardevice();
	sound( 1000 );
	delay( 600 );
	setcolor( RED );
	settextstyle( TRIPLEX_FONT, 0, 7 );
	settextjustify( CENTER_TEXT, CENTER_TEXT );
	outtextxy( getmaxx()/2, 50, "Result" );
	settextstyle( SCRIPT_FONT, 0, 5 );
	settextjustify( LEFT_TEXT, LEFT_TEXT );
	setcolor( LIGHTRED );
	outtextxy( 50, getmaxy()/2, "You :" );
	outtextxy( 35, getmaxy()/2+80, "CPU :" );
	setcolor( BLUE );
	outtextxy( 200, getmaxy()/2, itoa( p1.win, w1, 10 ) );
	outtextxy( 200, getmaxy()/2+80, itoa( p2.win, w2, 10 ) );
	sound( 700 );
	delay( 700 );
	nosound();
	if( p1.win-p2.win>preh )
	{
		TP.high = p1.win-p2.win;
		hi.seekp( 0 );
		hi.write( (char*)&TP, sizeof( TP ) );
	}
	getch();
}


void HTPTP()
{
	int inp = 0, page = 1;
	while( ( inp!=27 )&&( inp!=13 ) )
	{
		cleardevice();
		switch( inp )
		{
			case 75:
			page--;
			break;
			case 77:
			page++;
			break;
		}
		switch( page )
		{
			case 0:
			page = 8;
			break;
			case 9:
			page = 1;
			break;
		}
		switch( page )
		{
			case 1:
			setcolor( RED );
			settextstyle( TRIPLEX_FONT, 0, 7 );
			settextjustify( CENTER_TEXT, CENTER_TEXT );
			outtextxy( getmaxx()/2, 50, "How To Play" );
			settextstyle( SIMPLEX_FONT, 0, 1 );
			settextjustify( CENTER_TEXT, LEFT_TEXT );
			setcolor( BLUE );
			moveto( getmaxx()/2, getmaxy()/2 );
			outtext( "Browse next towards Increasing Priority...  ->" );
			outtextxy( getmaxx()/2, getmaxy()-30, "1" );
			break;
			case 7:
			setcolor( RED );
			settextstyle( TRIPLEX_FONT, 0, 3 );
			settextjustify( CENTER_TEXT, CENTER_TEXT );
			outtextxy( getmaxx()/2, 50, "TRIPLET" );
			settextstyle( SIMPLEX_FONT, 0, 1 );
			settextjustify( LEFT_TEXT, LEFT_TEXT );
			setcolor( BLUE );
			moveto( 30, getmaxy()/4 );
			outtext( "All Cards have Same Number. Example :" );
			outtextxy( getmaxx()/2, getmaxy()-30, "7" );
			graphdefaults();
			setbkcolor( WHITE );
			p2.card( p10x, p10y, 1, 10 );
			p2.card( p11x, p11y, 2, 10 );
			p2.card( p12x, p12y, 3, 10 );
			break;
			case 6:
			setcolor( RED );
			settextstyle( TRIPLEX_FONT, 0, 3 );
			settextjustify( CENTER_TEXT, CENTER_TEXT );
			outtextxy( getmaxx()/2, 50, "PURE SEQUENCE" );
			settextstyle( SIMPLEX_FONT, 0, 1 );
			settextjustify( LEFT_TEXT, LEFT_TEXT );
			setcolor( BLUE );
			moveto( 30, getmaxy()/4 );
			outtext( "All Cards have Same Shape, and Numbers in Sequence. Example :" );
			outtextxy( getmaxx()/2, getmaxy()-30, "6" );
			graphdefaults();
			setbkcolor( WHITE );
			p2.card( p10x, p10y, 3, 8 );
			p2.card( p11x, p11y, 3, 7 );
			p2.card( p12x, p12y, 3, 9 );
			break;
			case 5:
			setcolor( RED );
			settextstyle( TRIPLEX_FONT, 0, 3 );
			settextjustify( CENTER_TEXT, CENTER_TEXT );
			outtextxy( getmaxx()/2, 50, "SEQUENCE" );
			settextstyle( SIMPLEX_FONT, 0, 1 );
			settextjustify( LEFT_TEXT, LEFT_TEXT );
			setcolor( BLUE );
			moveto( 30, getmaxy()/4 );
			outtext( "All Numbers are in Sequence. Example :" );
			outtextxy( getmaxx()/2, getmaxy()-30, "5" );
			graphdefaults();
			setbkcolor( WHITE );
			p2.card( p10x, p10y, 3, 8 );
			p2.card( p11x, p11y, 2, 7 );
			p2.card( p12x, p12y, 1, 9 );
			break;
			case 4:
			setcolor( RED );
			settextstyle( TRIPLEX_FONT, 0, 3 );
			settextjustify( CENTER_TEXT, CENTER_TEXT );
			outtextxy( getmaxx()/2, 50, "COLOUR" );
			settextstyle( SIMPLEX_FONT, 0, 1 );
			settextjustify( LEFT_TEXT, LEFT_TEXT );
			setcolor( BLUE );
			moveto( 30, getmaxy()/4 );
			outtext( "All Cards have Same Shape. Example :" );
			outtextxy( getmaxx()/2, getmaxy()-30, "4" );
			graphdefaults();
			setbkcolor( WHITE );
			p2.card( p10x, p10y, 1, 1 );
			p2.card( p11x, p11y, 1, 5 );
			p2.card( p12x, p12y, 1, 12 );
			break;
			case 3:
			setcolor( RED );
			settextstyle( TRIPLEX_FONT, 0, 3 );
			settextjustify( CENTER_TEXT, CENTER_TEXT );
			outtextxy( getmaxx()/2, 50, "PAIR" );
			settextstyle( SIMPLEX_FONT, 0, 1 );
			settextjustify( LEFT_TEXT, LEFT_TEXT );
			setcolor( BLUE );
			moveto( 30, getmaxy()/4 );
			outtext( "Any Two Numbers are same. Example :" );
			outtextxy( getmaxx()/2, getmaxy()-30, "3" );
			graphdefaults();
			setbkcolor( WHITE );
			p2.card( p10x, p10y, 1, 5 );
			p2.card( p11x, p11y, 3, 5 );
			p2.card( p12x, p12y, 4, 2 );
			break;
			case 2:
			setcolor( RED );
			settextstyle( TRIPLEX_FONT, 0, 3 );
			settextjustify( CENTER_TEXT, CENTER_TEXT );
			outtextxy( getmaxx()/2, 50, "HIGH CARD" );
			settextstyle( SIMPLEX_FONT, 0, 1 );
			settextjustify( LEFT_TEXT, LEFT_TEXT );
			setcolor( BLUE );
			moveto( 30, getmaxy()/4 );
			outtext( "When no Special Set comes, Highest Numbers Wins. Example :" );
			outtextxy( getmaxx()/2, getmaxy()-30, "2" );
			graphdefaults();
			setbkcolor( WHITE );
			p2.card( p10x, p10y, 1, 13 );
			p2.card( p11x, p11y, 2, 5 );
			p2.card( p12x, p12y, 4, 2 );
			break;
			case 8:
			setcolor( RED );
			settextstyle( TRIPLEX_FONT, 0, 3 );
			settextjustify( CENTER_TEXT, CENTER_TEXT );
			outtextxy( getmaxx()/2, 50, "IF SIMILAR" );
			settextstyle( SIMPLEX_FONT, 0, 1 );
			settextjustify( LEFT_TEXT, LEFT_TEXT );
			setcolor( BLUE );
			moveto( 30, getmaxy()/4 );
			outtext( "If both Players have Similar Set," );
			moveto( 30, getmaxy()/4+25 );
			outtext( "Then the one with Higher Card Wins." );
			outtextxy( getmaxx()/2, getmaxy()-30, "8" );
			break;
		}
		sound( 800+70*page );
		delay( 60 );
		nosound();
		inp = getch();
	}
}


void countdown()
{
	int s;
	cleardevice();
	setcolor( RED );
	settextstyle( 4, 0, 0 );
	for( s = 15; s>0; s-- )
	{
		setusercharsize( s, 1, s, 1 );
		outtextxy( getmaxx()/2-105+105/s, 0, "3" );
		sound( 1200-50*s );
		delay( 50 );
		cleardevice();
	}
	for( s = 15; s>0; s-- )
	{
		setusercharsize( s, 1, s, 1 );
		outtextxy( getmaxx()/2-105+105/s, 0, "2" );
		sound( 1200-50*s );
		delay( 50 );
		cleardevice();
	}
	for( s = 15; s>0; s-- )
	{
		setusercharsize( s, 1, s, 1 );
		outtextxy( getmaxx()/2-105+105/s, 0, "1" );
		sound( 1200-50*s );
		delay( 50 );
		cleardevice();
	}
	nosound();
}


void distribute()
{
	int x0, x1, x2;
	setcolor( BLUE );
	setfillstyle( 6, BLUE );
	for( x0 = x2 = getmaxx()/2; x0>p00x; x0 -= 4, x2 += 4 )
	{
		cleardevice();
		bar( x0-30, p00y-60, x0+30, p00y+60 );
		bar( x2-30, p02y-60, x2+30, p02y+60 );
		bar( p01x-30, p01y-60, p01x+30, p01y+60 );
		bar( x0-30, p10y-60, x0+30, p10y+60 );
		bar( x2-30, p12y-60, x2+30, p12y+60 );
		bar( p01x-30, p11y-60, p01x+30, p11y+60 );
		sound( ( 5*x2 )-1000 );
		delay( 12 );
	}
	nosound();
	delay( 1000 );
	randomize();
	sound( 1500 );
	int d[6], temp, i, j, flag;
	for( i = 0; i<6; i++ )
	{
	again:
		flag = 0;
		temp = random( 52 )+1;
		for( j = 0; j<i; j++ )
		{
			if( ( temp==d[j] )||( temp<1 ) )
			{
				flag = 1;
			}
		}
		if( flag==1 )
		{
			goto again;
		}
		else d[i] = temp;
	}
	p1.s[0] = ( ( d[0]-1 )/13 )+1;
	p1.s[1] = ( ( d[1]-1 )/13 )+1;
	p1.s[2] = ( ( d[2]-1 )/13 )+1;
	p2.s[0] = ( ( d[3]-1 )/13 )+1;
	p2.s[1] = ( ( d[4]-1 )/13 )+1;
	p2.s[2] = ( ( d[5]-1 )/13 )+1;
	p1.n[0] = d[0]-( p1.s[0]-1 )*13;
	p1.n[1] = d[1]-( p1.s[1]-1 )*13;
	p1.n[2] = d[2]-( p1.s[2]-1 )*13;
	p2.n[0] = d[3]-( p2.s[0]-1 )*13;
	p2.n[1] = d[4]-( p2.s[1]-1 )*13;
	p2.n[2] = d[5]-( p2.s[2]-1 )*13;
	cleardevice();
	p1.card( p00x, p00y, p1.s[0], p1.n[0] );
	p1.card( p01x, p01y, p1.s[1], p1.n[1] );
	p1.card( p02x, p02y, p1.s[2], p1.n[2] );
	p2.card( p10x, p10y, p2.s[0], p2.n[0] );
	p2.card( p11x, p11y, p2.s[1], p2.n[1] );
	p2.card( p12x, p12y, p2.s[2], p2.n[2] );
	delay( 60 );
	nosound();
	settextstyle( 5, 0, 0 );
	setusercharsize( 7, 2, 7, 2 );
	setusercharsize( 3, 1, 7, 2 );
	setcolor( MAGENTA );
	outtextxy( p00x-235, p00y-85, "You" );
	outtextxy( p10x-230, p12y-85, "CPU" );
}


void Player::card( int x, int y, int s, int n )
{
	if( s==1||s==3 ) setcolor( RED );
	else setcolor( BLUE );
	rectangle( x-30, y-60, x+30, y+60 );
	shape( x, y, s );
	num( x, y, n );
}


void Player::shape( int& x, int& y, int& s )
{
	switch( s )
	{
		case HEART:
		settextstyle( 9, 1, 1 );
		outtextxy( x-19, y+5, "3" );
		settextstyle( 9, 0, 1 );
		outtextxy( x-7, y+14, "V" );
		break;
		case DIAMOND:
		line( x+1, y+10, x-11, y+28 );
		line( x-11, y+28, x+1, y+46 );
		line( x+1, y+46, x+13, y+28 );
		line( x+13, y+28, x+1, y+10 );
		break;
		case SPADE:
		setcolor( BLUE );
		line( x, y+10, x-12, y+28 );
		line( x, y+10, x+12, y+28 );
		rectangle( x-2, y+28, x+2, y+46 );
		setcolor( WHITE );
		rectangle( x-2, y+28, x+2, y+30 );
		setcolor( BLUE );
		arc( x-6, y+28, 180, 360, 6 );
		arc( x+6, y+28, 180, 360, 6 );
		break;
		case CLUB:
		setcolor( BLUE );
		arc( x, y+22, 354, 186, 7 );
		arc( x-5, y+30, 95, 285, 7 );
		arc( x+5, y+30, 255, 85, 7 );
		rectangle( x-3, y+28, x+3, y+46 );
		setcolor( WHITE );
		rectangle( x-3, y+28, x+3, y+36 );
		setcolor( BLUE );
		break;
	}
}


void Player::num( int& x, int& y, int& n )
{
	settextstyle( 1, 0, 4 );
	switch( n )
	{
		case 1:
		outtextxy( x-6, y-50, "2" );
		break;
		case 2:
		outtextxy( x-6, y-50, "3" );
		break;
		case 3:
		outtextxy( x-6, y-50, "4" );
		break;
		case 4:
		outtextxy( x-6, y-50, "5" );
		break;
		case 5:
		outtextxy( x-6, y-50, "6" );
		break;
		case 6:
		outtextxy( x-6, y-50, "7" );
		break;
		case 7:
		outtextxy( x-6, y-50, "8" );
		break;
		case 8:
		outtextxy( x-6, y-50, "9" );
		break;
		case 9:
		outtextxy( x-18, y-50, "10" );
		break;
		case 10:
		outtextxy( x-6, y-50, "J" );
		break;
		case 11:
		outtextxy( x-8, y-50, "Q" );
		break;
		case 12:
		outtextxy( x-9, y-50, "K" );
		break;
		case 13:
		outtextxy( x-9, y-50, "A" );
		break;
	}
}

void TPGame()
{
	graphdefaults();
	setbkcolor( WHITE );
	settextstyle( 5, 0, 0 );
	setcolor( BROWN );
	setusercharsize( 9, 4, 9, 4 );
	char s[16] = { 'S', 't', 'a', 'r', 't', ' ', 'T', 'h', 'e', ' ', 'g', 'a', 'm', 'e', ' ', '?' },
		t[16], no[2];
	int j, i;
	for( i = 0; i<16; i++, delay( 100 ) )
	{
		cleardevice();
		for( j = 0; j<=i; j++ )
		{
			t[j] = s[j];
		}
		t[i+1] = '\0';
		outtextxy( getmaxx()/2-285, getmaxy()/2-100, t );
		sound( 400+pow( 20*( 10+i ), i%2 ) );
	}
	settextstyle( 8, 0, 2 );
	setcolor( RED );
	nosound();
	delay( 500 );
	sound( 1000 );
	outtextxy( getmaxx()/2-40, getmaxy()/2, "(y/n)" );
	delay( 50 );
	nosound();
a:
	switch( getch() )
	{
		case 'y':
		break;
		case 'Y':
		break;
		case 'n':
		return;
		case 'N':
		return;
		default:
		goto a;
	}
	while( 1 )
	{
		countdown();
		delay( 500 );
		distribute();
		getch();
		i = getch();
		if( ( i==72 )||( i==75 )||( i==77 )||( i==80 ) )
		{
			getch();
		}
		if( compare( p1.s[0], p1.s[1], p1.s[2],
					 p1.n[0], p1.n[1], p1.n[2],
					 p2.s[0], p2.s[1], p2.s[2],
					 p2.n[0], p2.n[1], p2.n[2] ) )
		{
			p1.win++;
			for( int y = p01y; y<=getmaxy()/2; y += 4 )
			{
				cleardevice();
				p1.card( p00x, y, p1.s[0], p1.n[0] );
				p1.card( p01x, y, p1.s[1], p1.n[1] );
				p1.card( p02x, y, p1.s[2], p1.n[2] );
				delay( 25 );
				sound( 600+y*3 );
			}
			nosound();
			settextstyle( 5, 0, 8 );
			setcolor( MAGENTA );
			delay( 1000 );
			sound( 800 );
			outtextxy( getmaxx()/2-150, getmaxy()/2-200, "You Win" );
			delay( 50 );
			sound( 1100 );
			delay( 200 );
			nosound();
		}
		else
		{
			p2.win++;
			for( int y = p11y; y>=getmaxy()/2; y -= 4 )
			{
				cleardevice();
				p2.card( p10x, y, p2.s[0], p2.n[0] );
				p2.card( p11x, y, p2.s[1], p2.n[1] );
				p2.card( p12x, y, p2.s[2], p2.n[2] );
				delay( 25 );
				sound( 2*y );
			}
			nosound();
			settextstyle( 5, 0, 8 );
			setcolor( MAGENTA );
			delay( 1000 );
			sound( 800 );
			outtextxy( getmaxx()/2-160, getmaxy()/2-200, "You Lose" );
			delay( 50 );
			sound( 500 );
			delay( 200 );
			nosound();
		}
		i = getch();
		if( ( i==72 )||( i==75 )||( i==77 )||( i==80 ) )
		{
			getch();
			getch();
		}
		cleardevice();
		no[1] = '\0';
		for( i = 10; ( i>0 )&&( !kbhit() ); i-- )
		{
			sound( 1500 );
			settextstyle( 5, 0, 5 );
			setcolor( BROWN );
			outtextxy( getmaxx()/2-125, getmaxy()/2-50, "Play Again ?" );
			setcolor( RED );
			settextstyle( 8, 0, 4 );
			no[0] = i+47;
			outtextxy( getmaxx()/2-20, getmaxy()/2+10, no );
			delay( 60 );
			nosound();
			delay( 940 );
			cleardevice();
		}
		if( no[0]=='0' )
		{
			return;
		}
	}
}


int compare( int& sa0, int& sa1, int& sa2,
			 int& na0, int& na1, int& na2,
			 int& sb0, int& sb1, int& sb2,
			 int& nb0, int& nb1, int& nb2 )
{

	if( ( na0==na1 )&&( na2==na0 ) )
	{
		if( ( nb0==nb0 )&&( nb2==nb0 ) )
		{
			if( na0>nb0 )
			{
				return 1;
			}
			else return 0;
		}
		else return 1;
	}

	if( ( nb0==nb1 )&&( nb2==nb0 ) )
	{
		if( ( na0==na0 )&&( na2==na0 ) )
		{
			if( nb0>na0 )
			{
				return 0;
			}
			else return 1;
		}
		else return 0;
	}
	else if(
		( ( na0==na1+1 )&&( na0==na2+2 ) )||( ( na2==na1+1 )&&( na2==na0+2 ) )||
		( ( na1==na2+1 )&&( na1==na0+2 ) )||( ( na0==na2+1 )&&( na0==na1+2 ) )||
		( ( na2==na0+1 )&&( na2==na1+2 ) )||( ( na1==na0+1 )&&( na1==na2+2 ) )
		)
	{
		if( ( sa0==sa1 )&&( sa0==sa2 ) )
		{
			if(
				( ( nb0==nb1+1 )&&( nb0==nb2+2 ) )||( ( nb2==nb1+1 )&&( nb2==nb0+2 ) )||
				( ( nb1==nb2+1 )&&( nb1==nb0+2 ) )||( ( nb0==nb2+1 )&&( nb0==nb1+2 ) )||
				( ( nb2==nb0+1 )&&( nb2==nb1+2 ) )||( ( nb1==nb0+1 )&&( nb1==nb2+2 ) )
				)
			{
				if( ( sb0==sb1 )&&( sb0==sb2 ) )
				{
					if( ( na0+na1+na2 )>( nb0+nb1+nb2 ) )
					{
						return 1;
					}
					else return 0;
				}
				else return 1;
			}
			else return 1;
		}
		else
		{
			if(
				( ( nb0==nb1+1 )&&( nb0==nb2+2 ) )||( ( nb2==nb1+1 )&&( nb2==nb0+2 ) )||
				( ( nb1==nb2+1 )&&( nb1==nb0+2 ) )||( ( nb0==nb2+1 )&&( nb0==nb1+2 ) )||
				( ( nb2==nb0+1 )&&( nb2==nb1+2 ) )||( ( nb1==nb0+1 )&&( nb1==nb2+2 ) )
				)
			{
				if( ( sb0==sb1 )&&( sb0==sb2 ) )
				{
					return 0;
				}
				else
				{
					if( ( na0+na1+na2 )>( nb0+nb1+nb2 ) )
					{
						return 1;
					}
					else return 0;
				}
			}
			else return 1;
		}
	}
	else if(
		( ( na0==13 )&&( na1==1 )&&( na2==2 ) )||( ( na2==13 )&&( na1==1 )&&( na0==2 ) )||
		( ( na1==13 )&&( na2==1 )&&( na0==2 ) )||( ( na0==13 )&&( na2==1 )&&( na1==2 ) )||
		( ( na2==13 )&&( na0==1 )&&( na1==2 ) )||( ( na1==13 )&&( na0==1 )&&( na2==2 ) )
		)
	{
		if(
			( ( nb0==13 )&&( nb1==1 )&&( nb2==2 ) )||( ( nb2==13 )&&( nb1==1 )&&( nb0==2 ) )||
			( ( nb1==13 )&&( nb2==1 )&&( nb0==2 ) )||( ( nb0==13 )&&( nb2==1 )&&( nb1==2 ) )||
			( ( nb2==13 )&&( nb0==1 )&&( nb1==2 ) )||( ( nb1==13 )&&( nb0==1 )&&( nb2==2 ) )
			)
		{
			if( greatest( na0, na1, na2 )==na0 )
			{
				if( greatest( nb0, nb1, nb2 )==nb0 )
				{
					if( sa0>sb0 ) return 1;
				}
				else if( greatest( nb0, nb1, nb2 )==nb1 )
				{
					if( sa0>sb1 ) return 1;
				}
				else if( greatest( nb0, nb1, nb2 )==nb2 )
				{
					if( sa0>sb2 ) return 1;
				}
			}
			else if( greatest( na0, na1, na2 )==na1 )
			{
				if( greatest( nb0, nb1, nb2 )==nb0 )
				{
					if( sa1>sb0 ) return 1;
				}
				else if( greatest( nb0, nb1, nb2 )==nb1 )
				{
					if( sa1>sb1 ) return 1;
				}
				else if( greatest( nb0, nb1, nb2 )==nb2 )
				{
					if( sa1>sb2 ) return 1;
				}
			}
			else if( greatest( na0, na1, na2 )==na2 )
			{
				if( greatest( nb0, nb1, nb2 )==nb0 )
				{
					if( sa2>sb0 ) return 1;
				}
				else if( greatest( nb0, nb1, nb2 )==nb1 )
				{
					if( sa2>sb1 ) return 1;
				}
				else if( greatest( nb0, nb1, nb2 )==nb2 )
				{
					if( sa2>sb2 ) return 1;
				}
			}
		}
		else return 1;
	}
	else if(
		( ( nb0==13 )&&( nb1==1 )&&( nb2==2 ) )||( ( nb2==13 )&&( nb1==1 )&&( nb0==2 ) )||
		( ( nb1==13 )&&( nb2==1 )&&( nb0==2 ) )||( ( nb0==13 )&&( nb2==1 )&&( nb1==2 ) )||
		( ( nb2==13 )&&( nb0==1 )&&( nb1==2 ) )||( ( nb1==13 )&&( nb0==1 )&&( nb2==2 ) )
		)
	{
		if(
			( ( na0==13 )&&( na1==1 )&&( na2==2 ) )||( ( na2==13 )&&( na1==1 )&&( na0==2 ) )||
			( ( na1==13 )&&( na2==1 )&&( na0==2 ) )||( ( na0==13 )&&( na2==1 )&&( na1==2 ) )||
			( ( na2==13 )&&( na0==1 )&&( na1==2 ) )||( ( na1==13 )&&( na0==1 )&&( na2==2 ) )
			)
		{
			if( greatest( nb0, nb1, nb2 )==nb0 )
			{
				if( greatest( na0, na1, na2 )==na0 )
				{
					if( sb0>sa0 ) return 0;
				}
				else if( greatest( nb0, nb1, nb2 )==nb1 )
				{
					if( sa0>sb1 ) return 0;
				}
				else if( greatest( nb0, nb1, nb2 )==nb2 )
				{
					if( sa0>sb2 ) return 0;
				}
			}
			else if( greatest( nb0, nb1, nb2 )==nb1 )
			{
				if( greatest( na0, na1, na2 )==na0 )
				{
					if( sb1>sa0 ) return 0;
				}
				else if( greatest( na0, na1, na2 )==na1 )
				{
					if( sb1>sa1 ) return 0;
				}
				else if( greatest( na0, na1, na2 )==na2 )
				{
					if( sb1>sa2 ) return 0;
				}
			}
			else if( greatest( nb0, nb1, nb2 )==nb2 )
			{
				if( greatest( na0, na1, na2 )==na0 )
				{
					if( sb2>sa0 ) return 0;
				}
				else if( greatest( na0, na1, na2 )==na1 )
				{
					if( sb2>sa1 ) return 0;
				}
				else if( greatest( na0, na1, na2 )==na2 )
				{
					if( sb2>sa2 ) return 0;
				}
			}
		}
		else return 0;
	}
	else if(
		( ( nb0==nb1+1 )&&( nb0==nb2+2 ) )||( ( nb2==nb1+1 )&&( nb2==nb0+2 ) )||
		( ( nb1==nb2+1 )&&( nb1==nb0+2 ) )||( ( nb0==nb2+1 )&&( nb0==nb1+2 ) )||
		( ( nb2==nb0+1 )&&( nb2==nb1+2 ) )||( ( nb1==nb0+1 )&&( nb1==nb2+2 ) )
		)
	{
		if( ( sb0==sb1 )&&( sb0==sb2 ) )
		{
			if(
				( ( na0==na1+1 )&&( na0==na2+2 ) )||( ( na2==na1+1 )&&( na2==na0+2 ) )||
				( ( na1==na2+1 )&&( na1==na0+2 ) )||( ( na0==na2+1 )&&( na0==na1+2 ) )||
				( ( na2==na0+1 )&&( na2==na1+2 ) )||( ( na1==na0+1 )&&( na1==na2+2 ) )
				)
			{
				if( ( sa0==sa1 )&&( sa0==sa2 ) )
				{
					if( ( nb0+nb1+nb2 )>( na0+na1+na2 ) )
					{
						return 0;
					}
					else return 1;
				}
				else return 0;
			}
			else return 0;
		}
		else
		{
			if(
				( ( na0==na1+1 )&&( na0==na2+2 ) )||( ( na2==na1+1 )&&( na2==na0+2 ) )||
				( ( na1==na2+1 )&&( na1==na0+2 ) )||( ( na0==na2+1 )&&( na0==na1+2 ) )||
				( ( na2==na0+1 )&&( na2==na1+2 ) )||( ( na1==na0+1 )&&( na1==na2+2 ) )
				)
			{
				if( ( sa0==sa1 )&&( sa0==sa2 ) )
				{
					return 1;
				}
				else
				{
					if( ( nb0+nb1+nb2 )>( na0+na1+na2 ) )
					{
						return 0;
					}
					else return 1;
				}
			}
			else return 0;
		}
	}
	else if( ( sa0==sa1 )&&( sa0==sa2 ) )
	{
		if( ( sb0==sb1 )&&( sb0==sb2 ) )
		{
			if( greatest( na0, na1, na2 )>greatest( nb0, nb1, nb2 ) )
			{
				return 1;
			}
			else if( greatest( na0, na1, na2 )==greatest( nb0, nb1, nb2 ) )
			{
				if( greater( na0, na1, na2 )>greater( nb0, nb1, nb2 ) )
				{
					return 1;
				}
				else if( greater( na0, na1, na2 )==greater( nb0, nb1, nb2 ) )
				{
					if( great( na0, na1, na2 )>great( nb0, nb1, nb2 ) )
					{
						return 1;
					}
					else if( great( na0, na1, na2 )==great( nb0, nb1, nb2 ) )
					{
						return 1;
					}
					else return 0;
				}
				else return 0;
			}
			else return 0;
		}
		else return 1;
	}
	else if( ( sb0==sb1 )&&( sb0==sb2 ) )
	{
		if( ( sa0==sa1 )&&( sa0==sa2 ) )
		{
			if( greatest( nb0, nb1, nb2 )>greatest( na0, na1, na2 ) )
			{
				return 0;
			}
			else if( greatest( nb0, nb1, nb2 )==greatest( na0, na1, na2 ) )
			{
				if( greater( nb0, nb1, nb2 )>greater( na0, na1, na2 ) )
				{
					return 0;
				}
				else if( greater( nb0, nb1, nb2 )==greater( na0, na1, na2 ) )
				{
					if( great( nb0, nb1, nb2 )>great( na0, na1, na2 ) )
					{
						return 0;
					}
					else if( great( nb0, nb1, nb2 )==great( na0, na1, na2 ) )
					{
						return 1;
					}
					else return 1;
				}
				else return 1;
			}
			else return 1;
		}
		else return 0;
	}
	else if( ( na0==na1 )||( na0==na2 )||( na1==na2 ) )
	{
		if( ( nb0==nb1 )||( nb0==nb2 )||( nb1==nb2 ) )
		{
			if( ( na0==na1 )||( nb0==nb1 ) )
			{
				if( na0>nb0 )
				{
					return 1;
				}
				else if( na0==nb0 )
				{
					if( na2>nb2 )
					{
						return 1;
					}
					else if( na2==nb2 )
					{
						if( sa0>sb0 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
			if( ( na0==na1 )||( nb0==nb2 ) )
			{
				if( na0>nb0 )
				{
					return 1;
				}
				else if( na0==nb0 )
				{
					if( na2>nb1 )
					{
						return 1;
					}
					else if( na2==nb1 )
					{
						if( sa0>sb0 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
			if( ( na0==na1 )||( nb1==nb2 ) )
			{
				if( na0>nb1 )
				{
					return 1;
				}
				else if( na0==nb1 )
				{
					if( na2>nb0 )
					{
						return 1;
					}
					else if( na2==nb0 )
					{
						if( sa0>sb1 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
			if( ( na0==na2 )||( nb0==nb1 ) )
			{
				if( na0>nb0 )
				{
					return 1;
				}
				else if( na0==nb0 )
				{
					if( na1>nb2 )
					{
						return 1;
					}
					else if( na1==nb2 )
					{
						if( sa0>sb0 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
			if( ( na1==na2 )||( nb0==nb1 ) )
			{
				if( na1>nb0 )
				{
					return 1;
				}
				else if( na1==nb0 )
				{
					if( na0>nb2 )
					{
						return 1;
					}
					else if( na0==nb2 )
					{
						if( sa1>sb0 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
			if( ( na0==na2 )||( nb0==nb2 ) )
			{
				if( na0>nb0 )
				{
					return 1;
				}
				else if( na0==nb0 )
				{
					if( na1>nb1 )
					{
						return 1;
					}
					else if( na1==nb1 )
					{
						if( sa0>sb0 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
			if( ( na1==na2 )||( nb1==nb2 ) )
			{
				if( na1>nb1 )
				{
					return 1;
				}
				else if( na1==nb1 )
				{
					if( na0>nb0 )
					{
						return 1;
					}
					else if( na0==nb0 )
					{
						if( sa1>sb1 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
			if( ( na0==na2 )||( nb1==nb2 ) )
			{
				if( na0>nb1 )
				{
					return 1;
				}
				else if( na0==nb1 )
				{
					if( na1>nb0 )
					{
						return 1;
					}
					else if( na1==nb0 )
					{
						if( sa0>sb1 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
			if( ( na1==na2 )||( nb0==nb2 ) )
			{
				if( na1>nb0 )
				{
					return 1;
				}
				else if( na1==nb0 )
				{
					if( na0>nb1 )
					{
						return 1;
					}
					else if( na0==nb1 )
					{
						if( sa1>sb0 )
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else return 0;
			}
		}
		else return 1;
	}
	else if( ( nb0==nb1 )||( nb0==nb2 )||( nb1==nb2 ) )
	{
		if( ( na0==na1 )||( na0==na2 )||( na1==na2 ) )
		{
			if( ( nb0==nb1 )||( na0==na1 ) )
			{
				if( nb0>na0 )
				{
					return 0;
				}
				else if( nb0==na0 )
				{
					if( nb2>na2 )
					{
						return 0;
					}
					else if( nb2==na2 )
					{
						if( sb0>sa0 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
			if( ( nb0==nb1 )||( na0==na2 ) )
			{
				if( nb0>na0 )
				{
					return 0;
				}
				else if( nb0==na0 )
				{
					if( nb2>na1 )
					{
						return 0;
					}
					else if( nb2==na1 )
					{
						if( sb0>sa0 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
			if( ( nb0==nb1 )||( na1==na2 ) )
			{
				if( nb0>na1 )
				{
					return 0;
				}
				else if( nb0==na1 )
				{
					if( nb2>na0 )
					{
						return 0;
					}
					else if( nb2==na0 )
					{
						if( sb0>sa1 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
			if( ( nb0==nb2 )||( na0==na1 ) )
			{
				if( nb0>na0 )
				{
					return 0;
				}
				else if( nb0==na0 )
				{
					if( nb1>na2 )
					{
						return 0;
					}
					else if( nb1==na2 )
					{
						if( sb0>sa0 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
			if( ( nb1==nb2 )||( na0==na1 ) )
			{
				if( nb1>na0 )
				{
					return 0;
				}
				else if( nb1==na0 )
				{
					if( nb0>na2 )
					{
						return 0;
					}
					else if( nb0==na2 )
					{
						if( sb1>sa0 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
			if( ( nb0==nb2 )||( na0==na2 ) )
			{
				if( nb0>na0 )
				{
					return 0;
				}
				else if( nb0==na0 )
				{
					if( nb1>na1 )
					{
						return 0;
					}
					else if( nb1==na1 )
					{
						if( sb0>sa0 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
			if( ( nb1==nb2 )||( na1==na2 ) )
			{
				if( nb1>na1 )
				{
					return 0;
				}
				else if( nb1==na1 )
				{
					if( nb0>na0 )
					{
						return 0;
					}
					else if( nb0==na0 )
					{
						if( sb1>sa1 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
			if( ( nb0==nb2 )||( na1==na2 ) )
			{
				if( nb0>na1 )
				{
					return 0;
				}
				else if( nb0==na1 )
				{
					if( nb1>na0 )
					{
						return 0;
					}
					else if( nb1==na0 )
					{
						if( sb0>sa1 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
			if( ( nb1==nb2 )||( na0==na2 ) )
			{
				if( nb1>na0 )
				{
					return 0;
				}
				else if( nb1==na0 )
				{
					if( nb0>na1 )
					{
						return 0;
					}
					else if( nb0==na1 )
					{
						if( sb1>sa0 )
						{
							return 0;
						}
						else return 1;
					}
					else return 1;
				}
				else return 1;
			}
		}
		else return 0;
	}
	else if( greatest( na0, na1, na2 )>greatest( nb0, nb1, nb2 ) )
	{
		return 1;
	}
	else if( greatest( na0, na1, na2 )==greatest( nb0, nb1, nb2 ) )
	{
		if( greater( na0, na1, na2 )>greater( nb0, nb1, nb2 ) )
		{
			return 1;
		}
		else if( greater( na0, na1, na2 )==greater( nb0, nb1, nb2 ) )
		{
			if( great( na0, na1, na2 )>great( nb0, nb1, nb2 ) )
			{
				return 1;
			}
			else if( great( na0, na1, na2 )==great( nb0, nb1, nb2 ) )
			{
				if( greatest( na0, na1, na2 )==na0 )
				{
					if( greatest( nb0, nb1, nb2 )==nb0 )
					{
						if( sa0>sb0 ) return 1;
					}
					else if( greatest( nb0, nb1, nb2 )==nb1 )
					{
						if( sa0>sb1 ) return 1;
					}
					else if( greatest( nb0, nb1, nb2 )==nb2 )
					{
						if( sa0>sb2 ) return 1;
					}
				}
				else if( greatest( na0, na1, na2 )==na1 )
				{
					if( greatest( nb0, nb1, nb2 )==nb0 )
					{
						if( sa1>sb0 ) return 1;
					}
					else if( greatest( nb0, nb1, nb2 )==nb1 )
					{
						if( sa1>sb1 ) return 1;
					}
					else if( greatest( nb0, nb1, nb2 )==nb2 )
					{
						if( sa1>sb2 ) return 1;
					}
				}
				else if( greatest( na0, na1, na2 )==na2 )
				{
					if( greatest( nb0, nb1, nb2 )==nb0 )
					{
						if( sa2>sb0 ) return 1;
					}
					else if( greatest( nb0, nb1, nb2 )==nb1 )
					{
						if( sa2>sb1 ) return 1;
					}
					else if( greatest( nb0, nb1, nb2 )==nb2 )
					{
						if( sa2>sb2 ) return 1;
					}
				}
			}
			else return 0;
		}
		else return 0;
	}
	else if( greatest( nb0, nb1, nb2 )>greatest( na0, na1, na2 ) )
	{
		return 0;
	}
	else if( greatest( nb0, nb1, nb2 )==greatest( na0, na1, na2 ) )
	{
		if( greater( nb0, nb1, nb2 )>greater( na0, na1, na2 ) )
		{
			return 0;
		}
		else if( greater( nb0, nb1, nb2 )==greater( na0, na1, na2 ) )
		{
			if( great( nb0, nb1, nb2 )>great( na0, na1, na2 ) )
			{
				return 0;
			}
			else if( great( nb0, nb1, nb2 )==great( na0, na1, na2 ) )
			{
				if( greatest( nb0, nb1, nb2 )==nb0 )
				{
					if( greatest( na0, na1, na2 )==na0 )
					{
						if( sb0>sa0 ) return 0;
					}
					else if( greatest( nb0, nb1, nb2 )==nb1 )
					{
						if( sa0>sb1 ) return 0;
					}
					else if( greatest( nb0, nb1, nb2 )==nb2 )
					{
						if( sa0>sb2 ) return 0;
					}
				}
				else if( greatest( nb0, nb1, nb2 )==nb1 )
				{
					if( greatest( na0, na1, na2 )==na0 )
					{
						if( sb1>sa0 ) return 0;
					}
					else if( greatest( na0, na1, na2 )==na1 )
					{
						if( sb1>sa1 ) return 0;
					}
					else if( greatest( na0, na1, na2 )==na2 )
					{
						if( sb1>sa2 ) return 0;
					}
				}
				else if( greatest( nb0, nb1, nb2 )==nb2 )
				{
					if( greatest( na0, na1, na2 )==na0 )
					{
						if( sb2>sa0 ) return 0;
					}
					else if( greatest( na0, na1, na2 )==na1 )
					{
						if( sb2>sa1 ) return 0;
					}
					else if( greatest( na0, na1, na2 )==na2 )
					{
						if( sb2>sa2 ) return 0;
					}
				}
			}
			else return 1;
		}
		else return 1;
	}
	else return 1;
	return 1;
}


int greatest( int& a, int& b, int& c )
{
	if( a>b&& a>c )
	{
		return a;
	}
	else if( b>a&& b>c )
	{
		return b;
	}
	else if( c>a&& c>b )
	{
		return c;
	}
	return c;
}


int greater( int& a, int& b, int& c )
{
	if( ( a>b&& b>c )||( c>b&& b>a ) )
	{
		return b;
	}
	else if( ( b>c&& c>a )||( a>c&& c>b ) )
	{
		return c;
	}
	else if( ( c>a&& a>b )||( b>a&& a>c ) )
	{
		return a;
	}
	return a;
}


int great( int& a, int& b, int& c )
{
	if( a<b&&a<c )
	{
		return a;
	}
	else if( b<a&&b<c )
	{
		return b;
	}
	else if( c<a&&c<b )
	{
		return c;
	}
	return c;
}