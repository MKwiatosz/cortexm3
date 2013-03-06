/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : cmd_parse.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides APIs for command parse.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "cmd.h"
#include <stdio.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  CMD_HISTORIES             5
#define  CMD_BUF_SIZE              128

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
cmd_t    *pcmds = NULL;
cmd_t    cmdHelp;
uint32_t logIn = FALSE;
uint32_t pos = 0;
char     cmdBuffer[CMD_BUF_SIZE] = {0};
uint32_t histBuf[CMD_HISTORIES][CMD_BUF_SIZE]={{0,0}};
uint32_t histPos[CMD_HISTORIES] = {0};
uint32_t histIns        = 0;
uint32_t histOutput     = 0;
uint32_t histInsWrap    = 0;
uint32_t histOutputWrap = 0;
uint32_t ConsoleStartFlg= 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void consoleVersionGet(uint8_t* major,uint8_t* sub,uint8_t* minor);
static uint32_t cmdIdxIncrease(uint32_t *pcmdIdx);
static void cmdFlushCopy(uint32_t cursorPos,char *pcmdBuf,char *pcmdSrc,uint32_t cmdLen);
static void cmdHelpDisp(char *parameters);
static void cmdHelpShow(cmd_t *bc,uint32_t maxCmdLen);
static void cmdProcess(char *cmd,uint32_t repeating);

/* Private variables ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : consoleVersionGet
* Description    : Get console version.
* Input          : Address for save value.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void consoleVersionGet(uint8_t* major,uint8_t* sub,uint8_t* minor)
{
  *major = CONSOLE_VER_MAJOR;
  *sub   = CONSOLE_VER_SUB;
  *minor = CONSOLE_VER_MINOR;
}

/*******************************************************************************
* Function Name  : cmdVersion
* Description    : command for display the console version
* Input          : parameter
* Output         : None.
* Return         : None.
*******************************************************************************/
void cmdVersion(char *param)
{
  uint8_t major, sub, minor;

  printf("\r+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  consoleVersionGet(&major, &sub, &minor);
  printf("\r\nconsole: v%d.%d.%d",major,sub,minor);
  printf("\r\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
}

/*******************************************************************************
* Function Name  : cmdIdxIncrease
* Description    : Increase the cmmand index in hsitory buffer 
*                  and initial it if overflow.
* Input          : pcmdIdx: pointer to index
* Output         : None.
* Return         : FALSE: not wrapp
*                  TRUE: wrap.
*******************************************************************************/
static uint32_t cmdIdxIncrease(uint32_t *pcmdIdx)
{
  uint32_t localIdx;
  uint32_t ret = FALSE;

  localIdx = *pcmdIdx;
  localIdx++;
  if(localIdx == CMD_HISTORIES )
  {
    localIdx = 0;
    ret = TRUE;
  }
  *pcmdIdx = localIdx;

  return ret;
}

/*******************************************************************************
* Function Name  : cmdFlushCopy
* Description    : copy the command from source to dest 
* Input          : 
* Output         : None.
* Return         : None.
*******************************************************************************/
static void cmdFlushCopy(uint32_t cursorPos,char *pcmdBuf,char *pcmdSrc,uint32_t cmdLen)
{
  if(cursorPos > 0) 
  {
    for(;cursorPos > 0;cursorPos--)
    {
      printf("\b \b");
      cmdBuffer[cursorPos] = '\0';
    }
  }
  memcpy(pcmdBuf, pcmdSrc, cmdLen);
}

/*******************************************************************************
* Function Name  : cmdHelpDisp
* Description    : Display the command message.
* Input          : parameters: command string
* Output         : None.
* Return         : None.
*******************************************************************************/
static void cmdHelpDisp(char *parameters)
{
  cmd_t    *bc = pcmds;
  uint32_t  i  = 0;

  /* See if the user asked for a particular help. */
  if(*parameters != '\0')
  {
    while(bc)
    {
      if(strcmp(bc->cmd, parameters) == 0)
      {
        cmdHelpShow(bc, strlen(bc->cmd));
        return;
      }
      bc = bc->pnext;
    }

    printf("\rno help for command `%s' found, try just `help'\n", parameters);
    return;
  }

  /* Display base command */
  printf("\r+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  printf("\r\n+ basic command                                           +");
  printf("\r\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
  while(bc)
  {
    printf("%-11s ", bc->cmd);
    i++;
    if(i == 4)
    {
      printf("\r\n");
      i = 0;
    }
    bc = bc->pnext;
  }
  if(i != 0) 
  {
    printf("\r\n");
  }

  printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
}

/*******************************************************************************
* Function Name  : cmdHelpShow
* Description    : display the specified command message.
* Input          : bc: command structure
*                  maxCmdLen: command length
* Output         : None.
* Return         : None.
*******************************************************************************/
static void cmdHelpShow(cmd_t *bc,uint32_t maxCmdLen)
{
  const char *help = bc->phelp;
  uint32_t helpLen = strlen(help);
  uint32_t spaces = 0; //maxCmdLen - strlen((char*)bc->cmd);
  uint32_t showThisLine = 0;
  uint32_t lineOne = TRUE;
  uint32_t c;

  printf("%s", bc->cmd);
  if(helpLen == 0)
  {
    printf(" - No help.\n");
    return;
  }

  while(helpLen)
  {
    while(spaces > 1)
    {
      printf(" ");
      spaces--;
    }
    if(lineOne)
    {
      printf(" - ");
    }
    spaces = maxCmdLen + 3; /* 3: " - " has three characters */
    lineOne = FALSE;

    /*
     * See if greater then the line length if so, work back from the end for a
     * space, tab or lf or cr.
     */

    if(helpLen > (78 - maxCmdLen - 3))
    {
      for(showThisLine = (78 - maxCmdLen - 3) - 1;showThisLine;showThisLine--)
        if ((help[showThisLine] == ' ') || (help[showThisLine] == '\n') 
            || (help[showThisLine] == '\r') )
          break;

      /* If showThisLine is 0, it is a very long word !! */
      if (showThisLine == 0)
        showThisLine = (78 - maxCmdLen - 3) - 1;
    }
    else
      showThisLine = helpLen;

    for(c = 0; c < showThisLine; c++)
    {
      if((help[c] == '\r') || (help[c] == '\n'))
      {
        showThisLine = c;
      }
      else
      {
        printf("%c", help[c]);
      }
    }

    printf("\r\n");

    help += showThisLine;
    helpLen -= showThisLine;

    /* Move past the line feeds or what ever else is being skipped.*/
    while(helpLen)
    {
      if((*help != '\r') && (*help != '\n'))
      {
        break;
      }
      if(*help != ' ')
      {
        help++;
        helpLen--;
        break;
      }
      help++;
      helpLen--;
    }
  }
}

/*******************************************************************************
* Function Name  : cmdProcess
* Description    : process the command.
* Input          : cmd: command string
*                  repeating: TRUE: repeat command, FALSE: new command
* Output         : None.
* Return         : None.
*******************************************************************************/
static void cmdProcess(char *cmd,uint32_t repeating)
{
  cmd_t *bc = pcmds;
  uint32_t idx = 0;
  uint32_t copy = 0;

  /* Strip the white space from the command. */
  while(cmd[idx] != '\0')
  {
    if((cmd[idx] != ' ')  &&
       (cmd[idx] != '\t') &&
       (cmd[idx] != '\r') &&
       (cmd[idx] != '\n')) 
    {
      break;
    }
    idx++;
  }

  if ( idx > 0 )
  {
    /* Reached a non-white space character, compact the string */
    while(cmd[idx] != '\0')
    {
      cmd[copy++] = cmd[idx++];
    }
    cmd[copy] = '\0';   
  }

  /* Index points to the end of the string, move backwards. */
  idx = strlen(cmd);

  while(idx > 0)
  {
    idx--;
    if((cmd[idx] == ' ') || (cmd[idx] == '\t') 
        || (cmd[idx] == '\r') || (cmd[idx] == '\n'))
    {
      cmd[idx] = '\0';
    }
    else 
    {
      break;
    }
  }

  /* Find the command. */
  idx = 0;

  while(cmd[idx] != '\0' )
  {
    if((cmd[idx] == ' ') || (cmd[idx] == '\t')
        || (cmd[idx] == '\r') || (cmd[idx] == '\n'))
    {
      break;
    }
    idx++;
  }
  cmd[idx] = '\0';
  while(bc)
  {
    if(strcmp(bc->cmd, cmd) == 0)
    {
      (bc->phandler)(cmd + idx + 1);
      return;
    }
    bc = bc->pnext;
  }

  printf("\rcommand `%s' not found, try `help'\n", cmd);
}

/*******************************************************************************
* Function Name  : cmdHelpInit
* Description    : Init help command
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void cmdHelpInit(void)
{
  cmdHelp.cmd      = "help";
  cmdHelp.phelp    = "Provides help for commands. Try `help <command>'";
  cmdHelp.phandler = cmdHelpDisp;
  cmdRegister(&cmdHelp);
}

/*******************************************************************************
* Function Name  : cmdBasicInit
* Description    : Initialize the base command structure.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void cmdBasicInit(void)
{
  cmd_t *pcmdArray = basic_cmd_array;

  while(pcmdArray->cmd != NULL)
  {
    cmdRegister(pcmdArray);
    pcmdArray += 1;
  }
}

/*******************************************************************************
* Function Name  : cmdRegister
* Description    : Register the command into the command list.
* Input          : bc: command structure
* Output         : None.
* Return         : None.
*******************************************************************************/
void cmdRegister(cmd_t *bc)
{
  cmd_t *prev;
  cmd_t *curr;

  bc->pnext = NULL;
  if(pcmds == NULL)
  {
    pcmds = bc;
  }
  else 
  {
    prev = NULL;
    curr = pcmds;
    while(curr) 
    {
      /* The list is sorted by alphabetic order. */
      if (strcmp(bc->cmd, curr->cmd) <= 0) 
      {
        bc->pnext = curr;
        if(prev)
        {
          prev->pnext = bc;
        }
        else
        {
          pcmds = bc;
        }
        return;
      }
      prev = curr;
      curr = curr->pnext;
    }
    
    /* Last on the list. */ 
    prev->pnext = bc;
  } 
}

/*******************************************************************************
* Function Name  : cmdProcess
* Description    : process the command.
* Input          : cmd: command string
*                  repeating: TRUE: repeat command, FALSE: new command
* Output         : None.
* Return         : None.
*******************************************************************************/
void cmdMonitor(void)
{
  char c;
  uint32_t repeating = 0;
  uint32_t histDownArw;
  static uint32_t upArrowCnt;

  if(ConsoleStartFlg)
  {
    c = (char)getkey();
  }
  else
  {
    c = '\r';
    ConsoleStartFlg = 1;
  }

  if(!logIn)
  {
    if(c == '\r')
    {
      logIn = TRUE;
      printf("\r\ncmd>");
    }
  }
  else
  {
    switch(c)
    {
      case '\b':
      case '\x7f':
        if(pos > 0)
        {
          printf("\b \b");
          pos--;
        }
        cmdBuffer[pos] = '\0';
        break;

      case '\r':  
      /* Process the command. */
      printf("\r\n");
      if(pos)
      {
        /* Do not place the same last command into the history if the same. */  
        if(strcmp((char *)histBuf[histIns], cmdBuffer))
        {
          if(cmdIdxIncrease(&histIns) == TRUE)
          {
            histInsWrap = 1;
          }
          memcpy(histBuf[histIns], cmdBuffer, CMD_BUF_SIZE);
          histPos[histIns] = pos;
        }
        histOutput = histIns;
        histOutputWrap = 0;
        upArrowCnt = 0;
        repeating = FALSE;
      } 
      if(pos)
      {
        cmdProcess(cmdBuffer, repeating);
        pos = 0;
        memset(cmdBuffer, 0, CMD_BUF_SIZE);
        printf("\n");
      }
      printf("\rcmd>");
      break;

      case '[': /* Non ASCII characters, arrow. */
        c = getkey();
        switch (c)
        {
          case 'A': /* Key: up arrow */
            if(histOutputWrap == 1)
            {
              if(histOutput == histIns)
              {
                break;
              }
            }   
            if(histInsWrap == 0)
            {
              if(histOutput == 0)
              {
                break;
              }
            }
            upArrowCnt++;
            cmdFlushCopy(pos,cmdBuffer,(char *)histBuf[histOutput],histPos[histOutput]);
            pos = histPos[histOutput];
            cmdBuffer[pos + 1] = '\0';
            printf(cmdBuffer);
            if(histInsWrap == 1)
            {
              if(histOutput == 0)
              {
                histOutput = CMD_HISTORIES - 1;
                histOutputWrap = 1;
              }
              else 
              {
                histOutput--;
              }
            }
            else
            {
              if(histOutput != 0)
              {
                /* Note that when wrap around does not occur, the least
                 * of index is 1 because it is the first one to be
                 * written.
                 */
                histOutput--;
              }
              /* Nothing to do with histOutput == 0,
               * because there is no more commands.
               */
            }
            break;

        case 'B': /* Key: down arrow */
          if(upArrowCnt <= 1)
            break;

          upArrowCnt--;
          cmdIdxIncrease(&histOutput);
          histDownArw = histOutput;
          cmdIdxIncrease(&histDownArw);
          cmdFlushCopy(pos,cmdBuffer,(char *)histBuf[histDownArw],histPos[histDownArw]);
          pos = histPos[histDownArw];
          cmdBuffer[pos + 1] = '\0';
          printf(cmdBuffer);
          break;

        case 'C': /* Key: right arrow */
          break;
        case 'D': /* Key: left arrow */
          break;
        default:
          break;
        }
        break;

      default:
        if((pos < (CMD_BUF_SIZE - 1)) && (c >= ' ') && (c <= 'z'))
        {
          cmdBuffer[pos++] = c;
          cmdBuffer[pos] = '\0';
          printf(cmdBuffer + pos - 1);
        }
        if( c == '\x7e' )
        {// '~'
          cmdBuffer[pos++] = c;
          cmdBuffer[pos] = '\0';
          printf(cmdBuffer + pos - 1);
        }
        break;
    }
  } /* else of if !logged_in */
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
