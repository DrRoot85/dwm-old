/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int horizpadbar        = 1;        /* horizontal padding for statusbar */
static const int vertpadbar         = 0;        /* vertical padding for statusbar */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 4;       /* vertical padding of bar */
static const int sidepad            = 14;       /* horizontal padding of bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
// static char font[]            = { "Hack:size=10:antialias=true:autohint=true", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true" , "terminus:style=Bold:size=10" ,"monospace:size=10" };
static const char *fonts[]          = { "Hack:size=9:antialias=true:autohint=true", "NotoColorEmoji:pixelsize=9:antialias=true:autohint=true" , "terminus:style=Bold:size=9" ,"monospace:size=9" };
// static char dmenufont[]       = { "Hack:size=12:antialias=true:autohint=true", "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true", "monospace:size=12" };
// static const char *fonts[]          = { font };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
};


static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask iscentered  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         0,		1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 1,    0,		0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         1,		0,          1,           1,        -1 },
	{ "mpv",     NULL,     NULL,           0,         1,		1,          1,           1,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,		0,          0,           1,        -1 }, /* xev */
	{ NULL,     "spterm",  NULL,	    SPTAG(0),	 1,		1,		1,	    -1,	 -1 },
	{ NULL,     "spfm",	  NULL,	    SPTAG(1),	 1,		1,		1,	    -1, 	 -1 },
	{ NULL,     "keepassxc", NULL,	    SPTAG(2),	 1,		0,		1,	    -1, 	 -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
//#include <X11/XF86keysym.h> /* makes XF86* keys work */

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
// #define TAGKEYS(KEY,TAG) \
// 	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
// 	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
// 	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
// 	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define TAGKEYS(KEY,TAG)                                                                                               \
       &((Keychord){1, {{MODKEY, KEY}},                                        view,           {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask, KEY}},                            toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                              tag,            {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},                  toggletag,      {.ui = 1 << TAG} }),

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd2[]  = { "kitty", NULL };
static const char *termcmd[]  = { "sakura", NULL };
static const char *clipcmd[] 	 = { "clipmenu", "-m", dmenumon, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL }; 
static const char *layoutmenu_cmd = "layoutmenu.sh";
static const char *layoutmenucmd[] = {"layoutmenu.sh", NULL};
//static const char *mute[]     = {"pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL};
//static const char *downbri[]  = {"xbacklight", "-dec", "5", NULL};
//static const char *upbri[]    = {"xbacklight", "-inc", "5", NULL};
//static const char *autowall[] = {"autowall", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },

};

#include "selfrestart.c"

// static const Key keys[] = {
static Keychord *keychords[] = {
	/* modifier                     key        function        argument */
	/*brightness control keys */
 //{ 0, XF86XK_MonBrightnessDown, spawn, {.v = downbri}},
 //{ 0, XF86XK_MonBrightnessUp,   spawn, {.v = upbri}},
 //{ 0, XF86XK_AudioMicMute,	   spawn, {.v = mute}},
 //{ 0, XF86XK_Tools,             spawn, {.v = autowall}},
/*  	{ 0, XF86XK_Explorer,          spawn, {.v = }},
	{ 0, XF86XK_LaunchA,           spawn, {.v = }},
  	{ 0, XF86XK_Search,            spawn, {.v = }},
  	{ 0, XF86XK_Display,           spawn, {.v = }},*/
	/* */
	 &((Keychord){1, {{MODKEY,                       XK_p}},      spawn,          {.v = dmenucmd } }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_Return}}, spawn,          {.v = termcmd2 } }),
	 // &((Keychord){1, {{MODKEY|ControlMask,           XK_Return}}, spawn,          {.v = termcmd } }),
	 &((Keychord){2, {{MODKEY, XK_e}, 	 {MODKEY, XK_e}},          spawn,          {.v = termcmd } }),
	 &((Keychord){1, {{MODKEY, 	                  	XK_c}}, 	   spawn, 	   {.v = clipcmd} }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_m}}, 	   spawn, 	   {.v = layoutmenucmd} }),
	 &((Keychord){1, {{MODKEY,                       XK_b}},      togglebar,      {0} }),
	 &((Keychord){1, {{MODKEY,                       XK_j}},      focusstack,     {.i = +1 } }),
	 &((Keychord){1, {{MODKEY,                       XK_k}},      focusstack,     {.i = -1 } }),
	 &((Keychord){1, {{MODKEY,                       XK_i}},      incnmaster,     {.i = +1 } }),
	 &((Keychord){1, {{MODKEY,                       XK_d}},      incnmaster,     {.i = -1 } }),
	 &((Keychord){1, {{MODKEY,                       XK_h}},      setmfact,       {.f = -0.05} }),
	 &((Keychord){1, {{MODKEY,                       XK_l}},      setmfact,       {.f = +0.05} }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_h}},      setcfact,       {.f = +0.25} }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_l}},      setcfact,       {.f = -0.25} }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_o}},      setcfact,       {.f =  0.00} }),
	 &((Keychord){1, {{MODKEY,                       XK_Return}}, zoom,           {0} }),
	 &((Keychord){1, {{MODKEY|Mod1Mask,              XK_u}},      incrgaps,       {.i = +1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask|ControlMask,  XK_u}},      incrgaps,       {.i = -1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask,              XK_i}},      incrigaps,      {.i = +1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask|ControlMask,  XK_i}},      incrigaps,      {.i = -1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask,              XK_o}},      incrogaps,      {.i = +1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask|ControlMask,  XK_o}},      incrogaps,      {.i = -1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask,              XK_6}},      incrihgaps,     {.i = +1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask|ControlMask,  XK_6}},      incrihgaps,     {.i = -1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask,              XK_7}},      incrivgaps,     {.i = +1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask|ControlMask,  XK_7}},      incrivgaps,     {.i = -1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask,              XK_8}},      incrohgaps,     {.i = +1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask|ControlMask,  XK_8}},      incrohgaps,     {.i = -1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask,              XK_9}},      incrovgaps,     {.i = +1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask|ControlMask,  XK_9}},      incrovgaps,     {.i = -1 } }),
	 &((Keychord){1, {{MODKEY|Mod1Mask,              XK_0}},      togglegaps,     {0} }),
	 &((Keychord){1, {{MODKEY|Mod1Mask|ControlMask,  XK_0}},      defaultgaps,    {0} }),
	 &((Keychord){1, {{MODKEY,                       XK_Tab}},    view,           {0} }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_c}},      killclient,     {0} }),
	 &((Keychord){1, {{MODKEY,                       XK_t}},      setlayout,      {.v = &layouts[0]} }),
	 &((Keychord){1, {{MODKEY,                       XK_f}},      setlayout,      {.v = &layouts[1]} }),
	 &((Keychord){1, {{MODKEY,                       XK_m}},      setlayout,      {.v = &layouts[2]} }),
	 &((Keychord){1, {{MODKEY,                       XK_space}},  setlayout,      {0} }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_space}},  togglefloating, {0} }),
	 &((Keychord){1, {{MODKEY,                       XK_0}},      view,           {.ui = ~0 } }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_0}},      tag,            {.ui = ~0 } }),
	 &((Keychord){1, {{MODKEY,                       XK_comma}},  focusmon,       {.i = -1 } }),
	 &((Keychord){1, {{MODKEY,                       XK_period}}, focusmon,       {.i = +1 } }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_comma}},  tagmon,         {.i = -1 } }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_period}}, tagmon,         {.i = +1 } }),
	 &((Keychord){1, {{ MODKEY|ShiftMask,            XK_minus}}, setborderpx,    {.i = -1 } }),
	 &((Keychord){1, {{ MODKEY|ShiftMask,            XK_plus}},  setborderpx,    {.i = +1 } }),
	 &((Keychord){1, {{ MODKEY|ShiftMask,            XK_numbersign}}, setborderpx,    {.i = 0 } }),
        &((Keychord){1, {{MODKEY,            		XK_y}},      togglescratch,  {.ui = 0 } }),
	 &((Keychord){1, {{MODKEY,            		XK_u}},      togglescratch,  {.ui = 1 } }),
	 &((Keychord){1, {{MODKEY,            		XK_x}},      togglescratch,  {.ui = 2 } }),
	 &((Keychord){1, {{MODKEY,                       XK_F5}},     xrdb,           {.v = NULL } }),
	 &((Keychord){1, {{MODKEY|ControlMask,	    	XK_l}},	 movekeyboard_x, {.i = 20} }),
	 &((Keychord){1, {{MODKEY|ControlMask,	    	XK_h}},	 movekeyboard_x, {.i = -20} }),
	 &((Keychord){1, {{MODKEY|ControlMask,	    	XK_j}},	 movekeyboard_y, {.i = 20} }),
	 &((Keychord){1, {{MODKEY|ControlMask,	    	XK_k}},	 movekeyboard_y, {.i = -20} }),
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_r}},      self_restart,   {0} }),
	 &((Keychord){1, {{MODKEY|ShiftMask,             XK_q}},      quit,           {0} }),
	 &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, XK_q}},      quit,           {1} }), 
};

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	// { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,         Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,         Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,         Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
