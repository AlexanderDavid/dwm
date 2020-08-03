/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 6;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *fonts[] = { "JetBrains Mono Medium Nerd Font:size=14",
			       "JoyPixels:pixelsize=17:antialias=true:autohint=true" };
static char dmenufont[] = "JetBrainsMono:size=10";
static const char col_bg[]  = "#282828";
static const char col_gray[]   = "#3c3836";
static const char col_white[]  = "#98971a";
static const char col_green[]  = "#689d6a";
static const char col_fg[]   = "#ebdbb2";
static const char col_red[]   = "#cc241d";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg, col_bg },
	[SchemeSel]  = { col_gray, col_green,  col_red  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-c", "-l", "20",
                                 "-bw", "2",  NULL};
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* STACKKEYS(MODKEY,                          focus) */
	/* STACKKEYS(MODKEY|ShiftMask,                push) */
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)

	{MODKEY, XK_comma, focusmon, {.i = +1}},
	{MODKEY, XK_period, focusmon, {.i = -1}},
	{MODKEY | ShiftMask, XK_comma, tagmon, {.i = +1}},
	{MODKEY | ShiftMask, XK_period, tagmon, {.i = -1}},

	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_o,		setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_o,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },

	{MODKEY, XK_0, view, {.ui = ~0}},
	{MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},

	{MODKEY, XK_Tab, view, {0}},
	{MODKEY, XK_q, killclient, {0}},
	{MODKEY, XK_i, incnmaster, {.i = +1}},
	{MODKEY | ShiftMask, XK_i, incnmaster, {.i = -1}},
	{MODKEY, XK_backslash, view, {0}},

	/* { MODKEY,			XK_a,		togglegaps,	{0} }, */
	/* { MODKEY|ShiftMask,		XK_a,		defaultgaps,	{0} }, */
	{MODKEY, XK_s, togglesticky, {0}},
	{MODKEY, XK_d, spawn, {.v = dmenucmd}},
	{MODKEY, XK_f, togglefullscr, {0}},
	/* {MODKEY, XK_g, shiftview, {.i = -1}}, */
	{MODKEY, XK_h, setmfact, {.f = -0.05}},
	{MODKEY, XK_l, setmfact, {.f = +0.05}},
	/* {MODKEY, XK_semicolon, shiftview, {.i = 1}}, */
	{MODKEY, XK_Return, spawn, {.v = termcmd}},
	/* {MODKEY | ShiftMask, XK_Return, togglescratch, {.v = scratchpadcmd}}, */

	/* {MODKEY, XK_z, incrgaps, {.i = +1}}, */
	/* {MODKEY | ShiftMask, XK_z, incrgaps, {.i = -1}}, */
	{ MODKEY | ShiftMask,	XK_b,	togglebar,	{0} },

	/* {MODKEY, XK_Page_Up, shiftview, {.i = -1}}, */
	/* {MODKEY, XK_Page_Down, shiftview, {.i = 1}}, */

	{MODKEY, XK_F2, quit, {0}},
	/* {MODKEY, XK_F5, xrdb, {.v = NULL}}, */
	{MODKEY, XK_space, zoom, {0}},
	{MODKEY | ShiftMask, XK_space, togglefloating, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  spawn,               1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

