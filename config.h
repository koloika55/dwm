/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define BROWSER "librewolf"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack:size=12" };
static const char dmenufont[]       = "Hack:size=12";
static const char normbgcolor[]		= "#020914";
static const char normbordercolor[]	= "#a8856c";
static const char normfgcolor[]		= "#f1be9b";
static const char selfgcolor[]		= "#f1be9b";
static const char selbgcolor[]		= "#63576E";
static const char selbordercolor[]	= "#770000";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor},
	[SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor},
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         0,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
#include "movestack.c"
#include <X11/XF86keysym.h> /* to use volume buttons on the keyboard */

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,		{.v = dmenucmd } },
	{ MODKEY,			XK_Return, spawn,		{.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,		{0} },
	{ MODKEY,                       XK_j,      focusstack,		{.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,		{.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,		{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,      incnmaster,		{.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,		{.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,		{.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,		{.i = -1 } },
	{ MODKEY,                       XK_space,  zoom,		{0} },
	{ MODKEY,                       XK_0,	   view,		{0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,		{0} },
	{ MODKEY,                       XK_y,      setlayout,		{.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,		{.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,		{.v = &layouts[2]} },
	{ MODKEY,			XK_f,      togglefullscr,	{0} },
	{ MODKEY,                       XK_0,      view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,			{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,		{.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,		{.i = +1 } },
	TAGKEYS(                        XK_1,				0)
	TAGKEYS(                        XK_2,				1)
	TAGKEYS(                        XK_3,				2)
	TAGKEYS(                        XK_4,				3)
	TAGKEYS(                        XK_5,				4)
	TAGKEYS(                        XK_6,				5)
	TAGKEYS(                        XK_7,				6)
	TAGKEYS(                        XK_8,				7)
	TAGKEYS(                        XK_9,				8)
	{ MODKEY|ShiftMask,             XK_p,      	quit,           {0} },
	{ 0,				XK_Print,	spawn,		{.v = (const char*[]){ "maimpick", NULL } } },	
	{ MODKEY,			XK_w,		spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,			XK_m,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ MODKEY|ShiftMask,		XK_m,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "alsamixer; kill -39 $(pidof dwmblocks)", NULL } } },
	{ MODKEY,                       XK_r,           spawn,          {.v = (const char*[]){ TERMINAL, "-e", "yazi", NULL } } },
	{ MODKEY|ShiftMask,             XK_r,           spawn,          {.v = (const char*[]){ TERMINAL, "-e", "btop", NULL } } },
	{ MODKEY,			XK_n,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "nvim", "-c", "VimwikiIndex", NULL } } },
	{ MODKEY,			XK_t,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "stig", NULL } } },
	{ MODKEY|ShiftMask,		XK_n,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "newsboat", NULL } } },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("xdotool type $(grep -v '^#' ~/.config/bookmarks | dmenu -i -l 50 | cut -d' ' -f1)") },
	{ MODKEY, 			XK_F5,		spawn,		SHCMD("setxkbmap us") },
	{ MODKEY, 			XK_F6,		spawn,		SHCMD("setxkbmap lv") },
	{ MODKEY, 			XK_F7,		spawn,		SHCMD("setxkbmap ru") },
	{ MODKEY,			XK_p,		spawn,		SHCMD("slock") },
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("amixer -q set Master toggle; kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("amixer -q set Master 5%+ unmute; kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("amixer -q set Master 5%- unmute; kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMicMute,	spawn,		SHCMD("amixer set Capture toggle; kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("brillo -qA 5") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("brillo -qU 5") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

