/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int gappx              = 10;
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "eww-bar"; 	/* Alternate bar class name */
static const char *fonts[]          = { "monospace:size=10" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#cad3f5", "#24273a", "#f5bde6" },
	[SchemeSel]  = { "#cad3f5", "#24273a", "#c6a0f6" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class			 instance    title       tags mask     isfloating   monitor */
	{ "Gimp",			 NULL,       NULL,       0,            1,           -1 },
	{ "TelegramDesktop", NULL,		 NULL,		 0,			   1,			-1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]	    = { "st", NULL };
static const char *spotlight[]      = { "rofi", "-show", "drun", NULL};
static const char *brightnessup[]   = { "light", "-As", "sysfs/backlight/amdgpu_bl0", "10", NULL};
static const char *brightnessdown[] = { "light", "-Us", "sysfs/backlight/amdgpu_bl0", "10", NULL};
static const char *volup[]          = { "pamixer", "-i", "10", NULL};
static const char *voldown[]        = { "pamixer", "-d", "10", NULL};
static const char *voltoggle[]      = { "pamixer", "-t"      , NULL};

static Key keys[] = {

	/*                                                    func keys                                                */
	/* modifier                     key                                     function        argument               */
	{ 0,							(unsigned int)XF86XK_MonBrightnessUp,   spawn,          {.v = brightnessup   } },
	{ 0,							(unsigned int)XF86XK_MonBrightnessDown, spawn,          {.v = brightnessdown } },
	{ 0,							(unsigned int)XF86XK_AudioRaiseVolume,  spawn,          {.v = volup          } },
	{ 0,							(unsigned int)XF86XK_AudioLowerVolume,  spawn,          {.v = voldown        } },
	{ 0,							(unsigned int)XF86XK_AudioMute       ,  spawn,          {.v = voltoggle      } },

	/*                                regular keys                               */
	/* modifier                     key        function          argument */
	{ MODKEY,			            XK_Return, spawn,            {.v = termcmd   } },
	{ MODKEY,			            XK_space,  spawn,            {.v = spotlight } },
	{ MODKEY,                       XK_b,      togglebar,        {0} },
	{ MODKEY,                       XK_j,      focusstack,       {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,       {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,       {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,       {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,         {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,         {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,             {0} },
	{ MODKEY,                       XK_Tab,    view,             {0} },
	{ MODKEY,		                XK_q,      killclient,       {0} },
	{ MODKEY,                       XK_t,	   togglefloating, {0} },
	{ MODKEY,                       XK_f,	   fullscreentoggle, {0} },
	{ MODKEY,                       XK_0,      view,             {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,              {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,         {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,           {.i = +1 } },
	TAGKEYS(                        XK_1,                        0)
	TAGKEYS(                        XK_2,                        1)
	TAGKEYS(                        XK_3,                        2)
	TAGKEYS(                        XK_4,                        3)
	TAGKEYS(                        XK_5,                        4)
	TAGKEYS(                        XK_6,                        5)
	TAGKEYS(                        XK_7,                        6)
	TAGKEYS(                        XK_8,                        7)
	TAGKEYS(                        XK_9,                        8)
	{ MODKEY|ShiftMask,             XK_e,      quit,             {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,           Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,           Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,        resizemouse,    {0} },
};

