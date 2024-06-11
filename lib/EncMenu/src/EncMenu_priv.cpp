#include "EncMenu.h"
#include "MenuSymbols.h"

void Menu::ActivateBacklightTimer()
{
    mFlags.backlight_enabled = true;
    backlight_timer = millis();
}

void Menu::SetBacklightTimeout(uint32_t timeout)
{
    ActivateBacklightTimer();
    backlight_timeout = timeout;
}

void Menu::setup_progressbar()
{
    _lcd->createChar(0, bar_start_0);
    _lcd->createChar(1, bar_start_1);
    _lcd->createChar(2, bar_middle_0);
    _lcd->createChar(3, bar_middle_1);
    _lcd->createChar(4, bar_middle_2);
    _lcd->createChar(5, bar_end_0);
    _lcd->createChar(6, bar_end_1);
    mFlags.bar_chars_inited = true;
    mFlags.num_chars_inited = false;
}

void Menu::draw_progressbar(uint16_t percent, byte start_row, byte start_col)
{
    byte remain;
    if (start_col > LCD_COL_COUNT)
    {
        return;
    }
    else
    {
        remain = BAR_END_POSITION - start_col - 1;
    }

    if (!mFlags.bar_chars_inited)
        setup_progressbar();

    _lcd->setCursor(start_col, start_row);
    byte bar_fill = map(percent, 0, 100, 0, remain * 2 - 2);

    for (byte i = 0; i < remain; ++i)
    {
        if (i == 0)
        {
            if (bar_fill > 0)
            {
                _lcd->write(1);
                bar_fill -= 1;
            }
            else
            {
                _lcd->write((byte)0); // debut
            }
        }
        else if (i == remain - 1)
        {
            if (bar_fill > 0)
            {
                _lcd->write(6);
            }
            else
            {
                _lcd->write(5);
            }
        }
        else
        {
            if (bar_fill >= 2)
            {
                _lcd->write(4);
                bar_fill -= 2;
            }
            else if (bar_fill == 1)
            {
                _lcd->write(3);
                bar_fill -= 1;
            }
            else
            {
                _lcd->write(2);
            }
        }
    }
}

uint8_t Menu::GetLinesCount(uint8_t scr)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < Lines; i++)
    {
        if (lines[scr][i].line_text != '\0')
            count++;
    }
    return count;
}

uint8_t Menu::GetScreensCount()
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < Screens; i++)
    {
        if (lines[i][0].line_text != '\0')
            count++;
    }
    return count;
}

void Menu::MenuClearLine(uint8_t row)
{
    _lcd->setCursor(1, row);
    for (uint8_t i = 1; i < LCD_COL_COUNT; i++)
    {
        _lcd->print(" ");
    }
}

// void Menu::GetLineValueType(MenuLine_t *line_ptr)
void Menu::GetLineValueType(uint8_t scr, uint8_t line)
{
    switch (lines[scr][line].val_type)
    {
    case (BOOL_t):
        _lcd->print(lines[scr][line].line_value->Bool);
        break;

    case (U8_t):
        _lcd->print(lines[scr][line].line_value->u8);
        break;

    case (U16_t):
        _lcd->print(lines[scr][line].line_value->u16);
        break;

    case (U32_t):
        _lcd->print(lines[scr][line].line_value->u32);
        break;

    default:
        //Serial.println("default!");
        //_lcd->print(lines[scr][line].line_value->u16);
        _lcd->print("*");
        break;

    }
}

void Menu::PrintOneLine(uint8_t scr, uint8_t line_index, uint8_t line_to_print)
{
    _lcd->setCursor(1, line_to_print);
    _lcd->print(line_index);
    _lcd->print('.');
    _lcd->print(lines[scr][line_index].line_text);

    switch (lines[scr][line_index].line_type)
    {
    case SWITCH:
        _lcd->setCursor(IND_POSITION, line_to_print);
        _lcd->print((lines[scr][line_index].line_value->Bool > 0) ? " ON" : "OFF");
        break;

    case BARGRAPH: 
        draw_progressbar(lines[scr][line_index].line_value->u16, line_to_print, START_BAR_POSITION);
        _lcd->setCursor(IND_POSITION, line_to_print);
        GetLineValueType(scr, line_index); 
        _lcd->print((lines[scr][line_index].line_value->u16 == 100) ? "" : "%");
        break;

    case NORMAL:
        if ((lines[scr][line_index].val_type > 2) && (lines[scr][line_index].line_value->u16) > 999)  // > U8_t
        {
            _lcd->setCursor(IND_POSITION - 1, line_to_print);
        }
        else
        {
            _lcd->setCursor(IND_POSITION, line_to_print);
        }

        GetLineValueType(scr, line_index);
        break;

    case NO_TYPE:

        break;

    default:
        break;
    }
}

void Menu::ScreensNavigation(LINE_TARGET_TYPE line_target, MENU_TARGET_TYPE screen_target)
{
    if (screen_target == PREVIOS_SCREEN)
    {
        focuce = 1;
        if (GetScreen() == 0)
        {
            scr_num = GetScreensCount() - 1;
            EncMenu(UPDATE_LINE, UPDATE_SCREEN);
            return; // to do return handler
        }
        else
        {
            scr_num--;
        }
    }
    else if (screen_target == NEXT_SCREEN)
    {
        scr_num++;
        focuce = 1;
    }
    // check if we have gone beyond the size of the array, if we have gone we return to the null element
    if (scr_num > Screens)
        scr_num = 0;

    if (line_target == PREVIOS_LINE)
    {
        focuce--;
    }
    else if (line_target == NEXT_LINE)
    {
        focuce++;
    }
    focuce = constrain(focuce, 1, (GetLinesCount(scr_num)));

    // The null character signals the end of the list of strings/screens
    if (lines[scr_num][0].line_text == '\0')
    {
        scr_num = 0;
        EncMenu(UPDATE_LINE, UPDATE_SCREEN);
        return;
    }

    if (lines[scr_num][focuce].line_text == '\0')
    {
        focuce--;
        EncMenu(UPDATE_LINE, UPDATE_SCREEN);
        return;
    }

    if (focuce < 1)
        focuce = 1;

    _lcd->clear();
    _lcd->setCursor(0, 0);
    //_lcd->home(); // _lcd->setCursor(0, 0); //todo
    _lcd->print(lines[scr_num][0].line_text);
    if (scr_num)
    {
        _lcd->setCursor(SCREEN_NUMBER_POS, 0);
        _lcd->print(screen_ind_icon);
        _lcd->print(scr_num);
    }

} // todo handle return

void Menu::DisplayFocuceLines(int8_t *focuce_pos)
{
    int8_t scr_lines = GetLinesCount(scr_num);
    if (!scr_lines)
    {
        return; // error no lines
    }
    else if (scr_lines < LCD_ROW_COUNT)
    {
        scr_lines = LCD_ROW_COUNT;
    }

    uint8_t untill_last_row = scr_lines - focuce;
    int8_t start_row_print = rows_to_update - untill_last_row;
    *focuce_pos = LCD_ROW_COUNT - untill_last_row;
    if (start_row_print < 0)
        start_row_print = 0;

    if (untill_last_row > rows_to_update)
    {
        untill_last_row = rows_to_update;
        *focuce_pos = 1;
    }

    uint8_t line_index = focuce - start_row_print;
    uint8_t line_to_print = 1;

    // display the lines in order until we hit the null character
    for (line_index = (focuce - start_row_print); line_index < (focuce + untill_last_row); line_index++)
    {
        printed_lines_indicator[line_to_print - 1] = (uint16_t)(lines[scr_num][line_index].line_value);
        PrintOneLine(scr_num, line_index, line_to_print);

        if ((lines[scr_num][focuce + 3].line_text != '\0') && (lines[scr_num][focuce + 1].line_text != '\0'))
        {
            _lcd->createChar(7, down_arrow);
            _lcd->setCursor(0, 3);
            _lcd->write(7);
        }

        if (lines[scr_num][line_index + 1].line_text == '\0')
            break;
        line_to_print++;
    }
#if LCD_ROW_COUNT > 2
    if (printed_lines_indicator[0] != (uint16_t)(lines[scr_num][1].line_value)); //to do check
    {
        _lcd->setCursor(0, 1);
        _lcd->print('^');
    }

    if ((lines[scr_num][focuce + 3].line_text != '\0') && (lines[scr_num][focuce + 1].line_text != '\0'))
    {
        _lcd->createChar(7, down_arrow);
        _lcd->setCursor(0, 3);
        _lcd->write(7);
    }
#endif
}

void Menu::DisplayCurrentCursor(int8_t focuce_pos)
{
    // set and draw current position cursor
    _lcd->setCursor(0, focuce_pos);
    if (mFlags.lineSelected == true)
    {
        _lcd->blink();
        _lcd->print(edit_cursor_icon);
    }
    else
    {
        _lcd->noBlink();
        _lcd->print(cursor_icon);
    }
    //_lcd->print(mFlags.lineSelected ? edit_cursor_icon : cursor_icon);
}

void Menu::EncMenu(LINE_TARGET_TYPE line_target, MENU_TARGET_TYPE screen_target)
{
    ScreensNavigation(line_target, screen_target);

    DisplayFocuceLines(&active_focuce);

    DisplayCurrentCursor(active_focuce);
}