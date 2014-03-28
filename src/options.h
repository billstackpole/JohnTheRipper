/*
 * This file is part of John the Ripper password cracker,
 * Copyright (c) 1996-98,2003,2006,2013 by Solar Designer
 *
 * ...with changes in the jumbo patch, by JimF and magnum (and various others?)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 */

/*
 * John's command line options definition.
 */

#ifndef _JOHN_OPTIONS_H
#define _JOHN_OPTIONS_H

#include "list.h"
#include "loader.h"
#include "getopt.h"

/*
 * Core Option flags bitmasks (low 32 bits):
 */
/* Some option that doesn't have its own flag is specified */
#define FLG_NONE			0x00000000
/* An action requested */
#define FLG_ACTION			0x00000001
/* Password files specified */
#define FLG_PASSWD			0x00000002
/* An option supports password files */
#define FLG_PWD_SUP			0x00000004
/* An option requires password files */
#define FLG_PWD_REQ			(0x00000008 | FLG_PWD_SUP)
/* A cracking mode enabled */
#define FLG_CRACKING_CHK		0x00000020
#define FLG_CRACKING_SUP		0x00000040
#define FLG_CRACKING_SET \
	(FLG_CRACKING_CHK | FLG_CRACKING_SUP | FLG_ACTION | FLG_PWD_REQ)
/* Wordlist mode enabled, options.wordlist is set to the file name, or
 * we get it from john.conf */
#define FLG_WORDLIST_CHK		0x00000080
#define FLG_WORDLIST_SET		(FLG_WORDLIST_CHK | FLG_CRACKING_SET)
/* Wordlist mode enabled, reading from stdin */
#define FLG_STDIN_CHK			0x00000100
#define FLG_STDIN_SET			(FLG_STDIN_CHK | FLG_WORDLIST_SET)
/* Wordlist rules enabled */
#define FLG_RULES			0x00000200
/* "Single crack" mode enabled */
#define FLG_SINGLE_CHK			0x00000400
#define FLG_SINGLE_SET			(FLG_SINGLE_CHK | FLG_CRACKING_SET)
/* Incremental mode enabled */
#define FLG_INC_CHK			0x00000800
#define FLG_INC_SET			(FLG_INC_CHK | FLG_CRACKING_SET)
/* Mask mode enabled */
#define FLG_MASK_CHK			0x00001000
#define FLG_MASK_SET			(FLG_MASK_CHK | FLG_CRACKING_SET)
/* External mode or word filter enabled */
#define FLG_EXTERNAL_CHK		0x00002000
#define FLG_EXTERNAL_SET \
	(FLG_EXTERNAL_CHK | FLG_ACTION | FLG_CRACKING_SUP | FLG_PWD_SUP)
/* Batch cracker */
#define FLG_BATCH_CHK			0x00004000
#define FLG_BATCH_SET			(FLG_BATCH_CHK | FLG_CRACKING_SET)
/* Stdout mode */
#define FLG_STDOUT			0x00008000
/* Restoring an interrupted session */
#define FLG_RESTORE_CHK			0x00010000
#define FLG_RESTORE_SET			(FLG_RESTORE_CHK | FLG_ACTION)
/* A session name is set */
#define FLG_SESSION			0x00020000
/* Print status of a session */
#define FLG_STATUS_CHK			0x00040000
#define FLG_STATUS_SET			(FLG_STATUS_CHK | FLG_ACTION)
/* Make a charset */
#define FLG_MAKECHR_CHK			0x00100000
#define FLG_MAKECHR_SET \
	(FLG_MAKECHR_CHK | FLG_ACTION | FLG_PWD_SUP)
/* Show cracked passwords */
#define FLG_SHOW_CHK			0x00200000
#define FLG_SHOW_SET \
	(FLG_SHOW_CHK | FLG_ACTION | FLG_PWD_REQ)
/* Perform a benchmark */
#define FLG_TEST_CHK			0x00400000
#define FLG_TEST_SET \
	(FLG_TEST_CHK | FLG_CRACKING_SUP | FLG_ACTION)
/* Passwords per salt requested */
#define FLG_SALTS			0x01000000
/* Ciphertext format forced */
#define FLG_FORMAT			0x02000000
/* Memory saving enabled */
#define FLG_SAVEMEM			0x04000000
/* Node number(s) specified */
#define FLG_NODE			0x10000000
/* fork() requested, and process count specified */
#define FLG_FORK			0x20000000

/* Note that 0x80000000 is taken for OPT_REQ_PARAM, see getopt.h */

/*
 * Jumbo Options flags bitmasks (high 32 bits)
 *
 * Tip: For your private patches, pick first free from MSB. When
 * sharing your patch, pick first free from LSB of high 32 bits.
 */
/* .pot file used as wordlist, options.wordlist is set to the file name, or
 * we use the active .pot file */
#define FLG_LOOPBACK_CHK		0x0000000100000000ULL
#define FLG_LOOPBACK_SET	  \
	(FLG_LOOPBACK_CHK | FLG_WORDLIST_SET | FLG_CRACKING_SET | FLG_DUPESUPP)
/* pipe mode enabled, reading from stdin with rules support */
#define FLG_PIPE_CHK			0x0000000200000000ULL
#define FLG_PIPE_SET			(FLG_PIPE_CHK | FLG_WORDLIST_SET)
/* Dynamic load of foreign format module */
#define FLG_DYNFMT			0x0000000400000000ULL
/* Turn off logging */
#define FLG_NOLOG			0x0000000800000000ULL
/* Log to stderr */
#define FLG_LOG_STDERR			0x0000001000000000ULL
/* Markov mode enabled */
#define FLG_MKV_CHK			0x0000002000000000ULL
#define FLG_MKV_SET			(FLG_MKV_CHK | FLG_CRACKING_SET)
/* Emit a status line for every password cracked */
#define FLG_CRKSTAT			0x0000004000000000ULL
/* Wordlist dupe suppression */
#define FLG_DUPESUPP			0x0000008000000000ULL
/* Force scalar mode */
#define FLG_SCALAR			0x0000010000000000ULL
/* Reject printable binaries */
#define FLG_REJECT_PRINTABLE		0x0000020000000000ULL
/* Skip self tests */
#define FLG_NOTESTS			0x0000040000000000ULL
#if HAVE_REXGEN
#define FLG_REGEX_CHK			0x0000080000000000ULL
#define FLG_REGEX_SET			(FLG_REGEX_CHK | FLG_CRACKING_SET)
#endif /* HAVE_REXGEN */

/*
 * Structure with option flags and all the parameters.
 */
struct options_main {
/* Option flags */
	opt_flags flags;

/* Password files */
	struct list_main *passwd;

/* Password file loader options */
	struct db_options loader;

/* Session name */
	char *session;

/* Ciphertext format name */
	char *format;

/* Ciphertext subformat name */
	char *subformat;

/* Wordlist file name */
	char *wordlist;

/* Incremental mode name or charset file name */
	char *charset;

/* Mask mode's mask */
	char *mask;

/* The non-default input character set (utf8, ansi, iso-8859-1, etc)
   as given by the user (might be with/without dash and lower/upper case
   or even an alias, like 'ansi' for ISO-8859-1) */
	char *encoding;

/* External mode or word filter name */
	char *external;

/* Markov stuff */
	char *mkv_param;
	char *mkv_stats;

/* Maximum plaintext length for stdout mode */
	int length;

/* Parallel processing options */
	char *node_str;
	unsigned int node_min, node_max, node_count, fork;

/* Configuration file name */
	char *config;

/* Can't use HAVE_WINDOWS_H here so the below need to be maintained */
#if defined (_MSC_VER) || defined (__MINGW32__) || defined (__CYGWIN32__)
/* if built for Win32, then the pipe/stdin is VERY slow.  We allow special
 * processing to use the pipe command, but in a -pipe=sharedmemoryfilename
 * so that the producer app, and JtR can be written to work properly with
 * named shared memory, which is MUCH faster than using a pipe to xfer data
 * between the 2 apps. */
	char *sharedmemoryfilename;
#endif

/* Maximum size of a wordlist file to be 'preloaded' into memory  */
	unsigned max_wordfile_memory;

/* number of times fix_state_delay is called in wordfile.c before  any fseek()
   is done. */
	unsigned max_fix_state_delay;

/* the wordlist rules section (default if none entered is Wordlist) */
	char *activewordlistrules;

/* the 'single' rules section (default if none entered is Single) */
	char *activesinglerules;

/* This is a 'special' flag.  It causes john to add 'extra' code to search for
 * some salted types, when we have only the hashes.  The only type supported is
 * PHPS (at this time.).  So PHPS will set this to a 1. OTherwise it will
 * always be zero.  LIKELY we will add the same type logic for the OSC
 * (mscommerse) type, which has only a 2 byte salt.  That will set this field
 * to be a 2.  If we add other types, then we will have other values which can
 * be assigned to this variable.  This var is set by the undocummented
 * --regen_lost_salts=#   */
	int regen_lost_salts;

/* wordfile character encoding 'stuff' */
/* The canonical name of chosen encoding. User might have said 'koi8r' but
   this string will be 'KOI8-R'. An empty string means default/old-style */
	char *encodingStr;
/* A variant of same string, usable in #defines */
	char *encodingDef;
	int ascii;
	int utf8;
	int iso8859_1;
	int iso8859_2;
	int iso8859_7;
	int iso8859_15;
	int koi8_r;
	int cp437;
	int cp737;
	int cp850;
	int cp852;
	int cp858;
	int cp866;
	int cp1250;
	int cp1251;
	int cp1252;
	int cp1253;

/* Show/log/store UTF-8 regardless of input decoding */
	int store_utf8;
	int report_utf8;

/* Write cracked passwords to log (default is just username) */
	int log_passwords;

#ifdef HAVE_DL
/* List of dll files to load for additional formats */
	struct list_main *fmt_dlls;
#endif

/* Requested max_keys_per_crypt (for testing purposes) */
	int force_maxkeys;

/* Requested MinLen (min plaintext_length) */
	int force_minlength;

/* Requested MaxLen (max plaintext_length) */
	int force_maxlength;

/* Graceful exit after this many seconds of cracking */
	int max_run_time;

/* Emit a status line every N seconds */
	int status_interval;

/* Resync pot file when saving */
	int reload_at_save;

/* Send a resync trigger (to others) when new cracks are written to pot */
	int reload_at_crack;

/* Pause/abort on trigger files */
	char *pause_file;
	char *abort_file;

/* Force dynamic format to always treat bare hashes as valid. If not set
   then dynamic format only uses bare hashes if -form=dynamic_xxx is used.
   If this is 'N', then original logic used.  If 'Y' or 'y' then we always
   use bare hashes as valid in dynamic. */
	char dynamic_bare_hashes_always_valid;

#ifdef HAVE_OPENCL
	char *ocl_platform;

/* Vector width of OpenCL kernel */
	unsigned int v_width;
#endif
#if defined(HAVE_OPENCL) || defined(HAVE_CUDA)
	struct list_main *gpu_devices;
#endif
/* -list=WHAT Get a config list (eg. a list of incremental modes available) */
	char *listconf;
/* Verbosity level, 1-5. Three is normal, lower is more quiet. */
	int verbosity;
/* Secure mode. Do not output, log or store cracked passwords. */
	int secure;
/* regular expression */
  char *rexgen;
};

extern struct options_main options;

/*
 * Initializes the options structure.
 */
extern void opt_init(char *name, int argc, char **argv, int show_usage);

/*
 * Prints the "hidden" options usage
 */
extern void opt_print_hidden_usage(void);

#endif
